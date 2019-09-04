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
struct strbuf {int dummy; } ;
struct repository {int different_commondir; int /*<<< orphan*/  commondir; int /*<<< orphan*/  gitdir; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int get_common_dir_noenv (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void repo_set_commondir(struct repository *repo,
			       const char *commondir)
{
	struct strbuf sb = STRBUF_INIT;

	free(repo->commondir);

	if (commondir) {
		repo->different_commondir = 1;
		repo->commondir = xstrdup(commondir);
		return;
	}

	repo->different_commondir = get_common_dir_noenv(&sb, repo->gitdir);
	repo->commondir = strbuf_detach(&sb, NULL);
}