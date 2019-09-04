#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pathspec {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  match; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFRESH_IN_PORCELAIN ; 
 int /*<<< orphan*/  REFRESH_QUIET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  refresh_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pathspec const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_index ; 
 char* xcalloc (int,int) ; 

__attribute__((used)) static void refresh(int verbose, const struct pathspec *pathspec)
{
	char *seen;
	int i;

	seen = xcalloc(pathspec->nr, 1);
	refresh_index(&the_index, verbose ? REFRESH_IN_PORCELAIN : REFRESH_QUIET,
		      pathspec, seen, _("Unstaged changes after refreshing the index:"));
	for (i = 0; i < pathspec->nr; i++) {
		if (!seen[i])
			die(_("pathspec '%s' did not match any files"),
			    pathspec->items[i].match);
	}
	free(seen);
}