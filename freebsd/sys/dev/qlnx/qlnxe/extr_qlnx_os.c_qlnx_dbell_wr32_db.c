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
typedef  scalar_t__ uint32_t ;
struct ecore_hwfn {scalar_t__ doorbells; struct ecore_dev* p_dev; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_dbells; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void
qlnx_dbell_wr32_db(void *hwfn, void *reg_addr, uint32_t value)
{
	struct ecore_dev	*cdev;
	struct ecore_hwfn	*p_hwfn;
	uint32_t	offset;

	p_hwfn = hwfn;

	cdev = p_hwfn->p_dev;

	offset = (uint32_t)((uint8_t *)reg_addr - (uint8_t *)(p_hwfn->doorbells));
	bus_write_4(((qlnx_host_t *)cdev)->pci_dbells, offset, value);

	return;
}