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
struct cdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEV_FWMEM (struct cdev*) ; 
 int EINVAL ; 
 int fwmem_mmap (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fw_mmap (struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nproto, vm_memattr_t *memattr)
{

	if (DEV_FWMEM(dev))
		return fwmem_mmap(dev, offset, paddr, nproto, memattr);

	return EINVAL;
}