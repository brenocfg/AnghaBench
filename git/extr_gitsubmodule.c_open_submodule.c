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
struct repository {int /*<<< orphan*/  submodule_prefix; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (struct repository*) ; 
 scalar_t__ repo_init (struct repository*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ submodule_to_gitdir (struct strbuf*,char const*) ; 
 struct repository* xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct repository *open_submodule(const char *path)
{
	struct strbuf sb = STRBUF_INIT;
	struct repository *out = xmalloc(sizeof(*out));

	if (submodule_to_gitdir(&sb, path) || repo_init(out, sb.buf, NULL)) {
		strbuf_release(&sb);
		free(out);
		return NULL;
	}

	/* Mark it as a submodule */
	out->submodule_prefix = xstrdup(path);

	strbuf_release(&sb);
	return out;
}