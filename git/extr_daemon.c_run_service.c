#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct hostinfo {int dummy; } ;
struct daemon_service {int enabled; int (* fn ) (struct argv_array const*) ;int /*<<< orphan*/  name; int /*<<< orphan*/  config_name; scalar_t__ overridable; } ;
struct argv_array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ access_hook ; 
 int daemon_error (char const*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  export_all_trees ; 
 int /*<<< orphan*/  git_config_get_bool (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  logerror (char*,char const*,...) ; 
 int /*<<< orphan*/  loginfo (char*,int /*<<< orphan*/ ,char const*) ; 
 char* path_ok (char const*,struct hostinfo*) ; 
 scalar_t__ run_access_hook (struct daemon_service*,char const*,char const*,struct hostinfo*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int stub1 (struct argv_array const*) ; 

__attribute__((used)) static int run_service(const char *dir, struct daemon_service *service,
		       struct hostinfo *hi, const struct argv_array *env)
{
	const char *path;
	int enabled = service->enabled;
	struct strbuf var = STRBUF_INIT;

	loginfo("Request %s for '%s'", service->name, dir);

	if (!enabled && !service->overridable) {
		logerror("'%s': service not enabled.", service->name);
		errno = EACCES;
		return daemon_error(dir, "service not enabled");
	}

	if (!(path = path_ok(dir, hi)))
		return daemon_error(dir, "no such repository");

	/*
	 * Security on the cheap.
	 *
	 * We want a readable HEAD, usable "objects" directory, and
	 * a "git-daemon-export-ok" flag that says that the other side
	 * is ok with us doing this.
	 *
	 * path_ok() uses enter_repo() and does whitelist checking.
	 * We only need to make sure the repository is exported.
	 */

	if (!export_all_trees && access("git-daemon-export-ok", F_OK)) {
		logerror("'%s': repository not exported.", path);
		errno = EACCES;
		return daemon_error(dir, "repository not exported");
	}

	if (service->overridable) {
		strbuf_addf(&var, "daemon.%s", service->config_name);
		git_config_get_bool(var.buf, &enabled);
		strbuf_release(&var);
	}
	if (!enabled) {
		logerror("'%s': service not enabled for '%s'",
			 service->name, path);
		errno = EACCES;
		return daemon_error(dir, "service not enabled");
	}

	/*
	 * Optionally, a hook can choose to deny access to the
	 * repository depending on the phase of the moon.
	 */
	if (access_hook && run_access_hook(service, dir, path, hi))
		return -1;

	/*
	 * We'll ignore SIGTERM from now on, we have a
	 * good client.
	 */
	signal(SIGTERM, SIG_IGN);

	return service->fn(env);
}