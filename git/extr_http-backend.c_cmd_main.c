#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct service_cmd {char* method; int /*<<< orphan*/  (* imp ) (struct strbuf*,char*) ;int /*<<< orphan*/  pattern; } ;
struct TYPE_3__ {size_t rm_eo; size_t rm_so; } ;
typedef  TYPE_1__ regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct service_cmd*) ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int bad_request (struct strbuf*,struct service_cmd*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  die_webcgi ; 
 int /*<<< orphan*/  die_webcgi_recursing ; 
 int /*<<< orphan*/  enter_repo (char*,int /*<<< orphan*/ ) ; 
 char* getdir () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  git_env_ulong (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  http_config () ; 
 int /*<<< orphan*/  max_request_buffer ; 
 int /*<<< orphan*/  not_found (struct strbuf*,char*,char*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 struct service_cmd* services ; 
 int /*<<< orphan*/  set_die_is_recursing_routine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_die_routine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_path () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct strbuf*,char*) ; 
 char* xmemdupz (char*,size_t) ; 

int cmd_main(int argc, const char **argv)
{
	char *method = getenv("REQUEST_METHOD");
	char *dir;
	struct service_cmd *cmd = NULL;
	char *cmd_arg = NULL;
	int i;
	struct strbuf hdr = STRBUF_INIT;

	set_die_routine(die_webcgi);
	set_die_is_recursing_routine(die_webcgi_recursing);

	if (!method)
		die("No REQUEST_METHOD from server");
	if (!strcmp(method, "HEAD"))
		method = "GET";
	dir = getdir();

	for (i = 0; i < ARRAY_SIZE(services); i++) {
		struct service_cmd *c = &services[i];
		regex_t re;
		regmatch_t out[1];

		if (regcomp(&re, c->pattern, REG_EXTENDED))
			die("Bogus regex in service table: %s", c->pattern);
		if (!regexec(&re, dir, 1, out, 0)) {
			size_t n;

			if (strcmp(method, c->method))
				return bad_request(&hdr, c);

			cmd = c;
			n = out[0].rm_eo - out[0].rm_so;
			cmd_arg = xmemdupz(dir + out[0].rm_so + 1, n - 1);
			dir[out[0].rm_so] = 0;
			break;
		}
		regfree(&re);
	}

	if (!cmd)
		not_found(&hdr, "Request not supported: '%s'", dir);

	setup_path();
	if (!enter_repo(dir, 0))
		not_found(&hdr, "Not a git repository: '%s'", dir);
	if (!getenv("GIT_HTTP_EXPORT_ALL") &&
	    access("git-daemon-export-ok", F_OK) )
		not_found(&hdr, "Repository not exported: '%s'", dir);

	http_config();
	max_request_buffer = git_env_ulong("GIT_HTTP_MAX_REQUEST_BUFFER",
					   max_request_buffer);

	cmd->imp(&hdr, cmd_arg);
	return 0;
}