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
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct remote {int configured_in_repo; int fetch_tags; int /*<<< orphan*/  push; int /*<<< orphan*/  fetch; int /*<<< orphan*/  name; int /*<<< orphan*/  origin; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  REMOTE_BRANCHES ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_url_alias (struct remote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refspec_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char*,...) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void read_branches_file(struct remote *remote)
{
	char *frag;
	struct strbuf buf = STRBUF_INIT;
	FILE *f = fopen_or_warn(git_path("branches/%s", remote->name), "r");

	if (!f)
		return;

	strbuf_getline_lf(&buf, f);
	fclose(f);
	strbuf_trim(&buf);
	if (!buf.len) {
		strbuf_release(&buf);
		return;
	}

	remote->configured_in_repo = 1;
	remote->origin = REMOTE_BRANCHES;

	/*
	 * The branches file would have URL and optionally
	 * #branch specified.  The "master" (or specified) branch is
	 * fetched and stored in the local branch matching the
	 * remote name.
	 */
	frag = strchr(buf.buf, '#');
	if (frag)
		*(frag++) = '\0';
	else
		frag = "master";

	add_url_alias(remote, strbuf_detach(&buf, NULL));
	strbuf_addf(&buf, "refs/heads/%s:refs/heads/%s",
		    frag, remote->name);
	refspec_append(&remote->fetch, buf.buf);

	/*
	 * Cogito compatible push: push current HEAD to remote #branch
	 * (master if missing)
	 */
	strbuf_reset(&buf);
	strbuf_addf(&buf, "HEAD:refs/heads/%s", frag);
	refspec_append(&remote->push, buf.buf);
	remote->fetch_tags = 1; /* always auto-follow */
	strbuf_release(&buf);
}