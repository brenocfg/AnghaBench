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
 int /*<<< orphan*/  free (char*) ; 
 char* get_default_remote () ; 
 scalar_t__ git_config_get_string (int /*<<< orphan*/ ,char**) ; 
 char* relative_url (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xgetcwd () ; 

__attribute__((used)) static char *compute_submodule_clone_url(const char *rel_url)
{
	char *remoteurl, *relurl;
	char *remote = get_default_remote();
	struct strbuf remotesb = STRBUF_INIT;

	strbuf_addf(&remotesb, "remote.%s.url", remote);
	if (git_config_get_string(remotesb.buf, &remoteurl)) {
		warning(_("could not look up configuration '%s'. Assuming this repository is its own authoritative upstream."), remotesb.buf);
		remoteurl = xgetcwd();
	}
	relurl = relative_url(remoteurl, rel_url, NULL);

	free(remote);
	free(remoteurl);
	strbuf_release(&remotesb);

	return relurl;
}