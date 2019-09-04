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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_config_get_string (int /*<<< orphan*/ ,char**) ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *get_default_remote(void)
{
	char *dest = NULL, *ret;
	struct strbuf sb = STRBUF_INIT;
	const char *refname = resolve_ref_unsafe("HEAD", 0, NULL, NULL);

	if (!refname)
		die(_("No such ref: %s"), "HEAD");

	/* detached HEAD */
	if (!strcmp(refname, "HEAD"))
		return xstrdup("origin");

	if (!skip_prefix(refname, "refs/heads/", &refname))
		die(_("Expecting a full ref name, got %s"), refname);

	strbuf_addf(&sb, "branch.%s.remote", refname);
	if (git_config_get_string(sb.buf, &dest))
		ret = xstrdup("origin");
	else
		ret = dest;

	strbuf_release(&sb);
	return ret;
}