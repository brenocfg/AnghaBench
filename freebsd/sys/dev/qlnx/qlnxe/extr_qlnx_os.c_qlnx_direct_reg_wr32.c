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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ecore_hwfn {struct ecore_dev* p_dev; } ;
struct ecore_dev {scalar_t__ regview; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_reg; } ;
typedef  TYPE_1__ qlnx_host_t ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void
qlnx_direct_reg_wr32(void *p_hwfn, void *reg_addr, uint32_t value)
{
	bus_size_t		offset;
	struct ecore_dev	*cdev;

	cdev = ((struct ecore_hwfn *)p_hwfn)->p_dev;
	offset = (bus_size_t)((uint8_t *)reg_addr - (uint8_t *)(cdev->regview));

	bus_write_4(((qlnx_host_t *)cdev)->pci_reg, offset, value);

	return;
}