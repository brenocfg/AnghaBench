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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct tty {int dummy; } ;
struct cdev {struct tty* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttydev_enter (struct tty*) ; 
 int ttydevsw_mmap (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ttydev_mmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{
	struct tty *tp = dev->si_drv1;
	int error;

	/* Handle mmap() through the driver. */

	error = ttydev_enter(tp);
	if (error)
		return (-1);
	error = ttydevsw_mmap(tp, offset, paddr, nprot, memattr);
	tty_unlock(tp);

	return (error);
}