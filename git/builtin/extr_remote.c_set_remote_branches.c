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
struct remote {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_branches (struct remote*,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 struct remote* remote_get (char const*) ; 
 int /*<<< orphan*/  remote_is_configured (struct remote*,int) ; 
 scalar_t__ remove_all_fetch_refspecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int set_remote_branches(const char *remotename, const char **branches,
				int add_mode)
{
	struct strbuf key = STRBUF_INIT;
	struct remote *remote;

	strbuf_addf(&key, "remote.%s.fetch", remotename);

	remote = remote_get(remotename);
	if (!remote_is_configured(remote, 1))
		die(_("No such remote '%s'"), remotename);

	if (!add_mode && remove_all_fetch_refspecs(key.buf)) {
		strbuf_release(&key);
		return 1;
	}
	add_branches(remote, branches, key.buf);

	strbuf_release(&key);
	return 0;
}