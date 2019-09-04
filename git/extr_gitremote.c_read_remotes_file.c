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
struct remote {int configured_in_repo; int /*<<< orphan*/  fetch; int /*<<< orphan*/  push; int /*<<< orphan*/  origin; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  REMOTE_REMOTES ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  add_url_alias (struct remote*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen_or_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refspec_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ skip_prefix (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  skip_spaces (char const*) ; 
 scalar_t__ strbuf_getline (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_remotes_file(struct remote *remote)
{
	struct strbuf buf = STRBUF_INIT;
	FILE *f = fopen_or_warn(git_path("remotes/%s", remote->name), "r");

	if (!f)
		return;
	remote->configured_in_repo = 1;
	remote->origin = REMOTE_REMOTES;
	while (strbuf_getline(&buf, f) != EOF) {
		const char *v;

		strbuf_rtrim(&buf);

		if (skip_prefix(buf.buf, "URL:", &v))
			add_url_alias(remote, xstrdup(skip_spaces(v)));
		else if (skip_prefix(buf.buf, "Push:", &v))
			refspec_append(&remote->push, skip_spaces(v));
		else if (skip_prefix(buf.buf, "Pull:", &v))
			refspec_append(&remote->fetch, skip_spaces(v));
	}
	strbuf_release(&buf);
	fclose(f);
}