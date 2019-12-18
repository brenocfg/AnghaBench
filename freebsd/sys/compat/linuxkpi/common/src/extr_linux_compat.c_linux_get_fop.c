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
typedef  int u_int ;
struct linux_file {struct file_operations* f_op; struct linux_cdev* f_cdev; } ;
struct linux_cdev {int siref; struct file_operations* ops; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 int LDEV_SI_DTR ; 
 scalar_t__ LDEV_SI_REF ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ atomic_fcmpset_int (int*,int*,scalar_t__) ; 
 struct linux_cdev dummy_ldev ; 

__attribute__((used)) static void
linux_get_fop(struct linux_file *filp, const struct file_operations **fop,
    struct linux_cdev **dev)
{
	struct linux_cdev *ldev;
	u_int siref;

	ldev = filp->f_cdev;
	*fop = filp->f_op;
	if (ldev != NULL) {
		for (siref = ldev->siref;;) {
			if ((siref & LDEV_SI_DTR) != 0) {
				ldev = &dummy_ldev;
				siref = ldev->siref;
				*fop = ldev->ops;
				MPASS((ldev->siref & LDEV_SI_DTR) == 0);
			} else if (atomic_fcmpset_int(&ldev->siref, &siref,
			    siref + LDEV_SI_REF)) {
				break;
			}
		}
	}
	*dev = ldev;
}