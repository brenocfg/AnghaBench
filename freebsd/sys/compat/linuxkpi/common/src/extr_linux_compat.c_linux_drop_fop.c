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
struct linux_cdev {int siref; } ;

/* Variables and functions */
 int LDEV_SI_DTR ; 
 int /*<<< orphan*/  LDEV_SI_REF ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
linux_drop_fop(struct linux_cdev *ldev)
{

	if (ldev == NULL)
		return;
	MPASS((ldev->siref & ~LDEV_SI_DTR) != 0);
	atomic_subtract_int(&ldev->siref, LDEV_SI_REF);
}