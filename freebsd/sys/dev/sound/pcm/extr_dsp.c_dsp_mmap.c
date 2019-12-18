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
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsp_mmap(struct cdev *i_dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{

	/*
	 * offset is in range due to checks in dsp_mmap_single().
	 * XXX memattr is not honored.
	 */
	*paddr = vtophys(offset);
	return (0);
}