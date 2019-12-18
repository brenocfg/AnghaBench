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
struct labhash {TYPE_1__* lh_cmd; int /*<<< orphan*/  lh_ref; struct labhash* lh_next; } ;
struct TYPE_2__ {int /*<<< orphan*/  t; } ;

/* Variables and functions */
 int LHSZ ; 
 int /*<<< orphan*/  fname ; 
 int /*<<< orphan*/  free (struct labhash*) ; 
 struct labhash** labels ; 
 int /*<<< orphan*/  linenum ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uselabel(void)
{
	struct labhash *lh, *next;
	int i;

	for (i = 0; i < LHSZ; i++) {
		for (lh = labels[i]; lh != NULL; lh = next) {
			next = lh->lh_next;
			if (!lh->lh_ref)
				warnx("%lu: %s: unused label '%s'",
				    linenum, fname, lh->lh_cmd->t);
			free(lh);
		}
	}
}