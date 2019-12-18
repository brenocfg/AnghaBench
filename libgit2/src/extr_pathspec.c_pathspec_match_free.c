#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  failures; int /*<<< orphan*/  matches; int /*<<< orphan*/ * pathspec; } ;
typedef  TYPE_1__ git_pathspec_match_list ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_array_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pathspec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pathspec_match_free(git_pathspec_match_list *m)
{
	if (!m)
		return;

	git_pathspec_free(m->pathspec);
	m->pathspec = NULL;

	git_array_clear(m->matches);
	git_array_clear(m->failures);
	git_pool_clear(&m->pool);
	git__free(m);
}