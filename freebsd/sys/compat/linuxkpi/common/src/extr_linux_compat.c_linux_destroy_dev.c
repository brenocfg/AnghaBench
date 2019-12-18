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
struct linux_cdev {int siref; int /*<<< orphan*/ * cdev; } ;

/* Variables and functions */
 int LDEV_SI_DTR ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int atomic_load_int (int*) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 

void
linux_destroy_dev(struct linux_cdev *ldev)
{

	if (ldev->cdev == NULL)
		return;

	MPASS((ldev->siref & LDEV_SI_DTR) == 0);
	atomic_set_int(&ldev->siref, LDEV_SI_DTR);
	while ((atomic_load_int(&ldev->siref) & ~LDEV_SI_DTR) != 0)
		pause("ldevdtr", hz / 4);

	destroy_dev(ldev->cdev);
	ldev->cdev = NULL;
}