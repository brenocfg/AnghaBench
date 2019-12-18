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
struct dirlist {int /*<<< orphan*/  printer; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct dirlist* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct dirlist* LIST_NEXT (struct dirlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dirlist ; 
 scalar_t__ equal (struct dirlist*,struct dirlist*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  problems ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
check_spool_dirs(void)
{
	struct dirlist *dp, *dp2;

	for (dp = LIST_FIRST(&dirlist); dp; dp = dp2) {
		dp2 = LIST_NEXT(dp, link);

		if (dp2 != NULL && equal(dp, dp2)) {
			++problems;
			if (strcmp(dp->path, dp2->path) == 0) {
				warnx("%s and %s share the same spool, %s",
				      dp->printer, dp2->printer, dp->path);
			} else {
				warnx("%s (%s) and %s (%s) are the same "
				      "directory", dp->path, dp->printer,
				      dp2->path, dp2->printer);
			}
			continue;
		}
		/* Should probably check owners and modes here. */
	}
}