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
struct cdevsw {int /*<<< orphan*/  d_flags; struct cdevsw* d_gianttrick; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INIT ; 
 int /*<<< orphan*/  cdevsw_free_devlocked (struct cdevsw*) ; 
 int /*<<< orphan*/  memcpy (struct cdevsw*,struct cdevsw*,int) ; 

__attribute__((used)) static void
fini_cdevsw(struct cdevsw *devsw)
{
	struct cdevsw *gt;

	if (devsw->d_gianttrick != NULL) {
		gt = devsw->d_gianttrick;
		memcpy(devsw, gt, sizeof *devsw);
		cdevsw_free_devlocked(gt);
		devsw->d_gianttrick = NULL;
	}
	devsw->d_flags &= ~D_INIT;
}