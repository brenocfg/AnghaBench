#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct ecore_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ pci_dbells; scalar_t__ pci_reg; struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_READ ; 
 int /*<<< orphan*/  bus_barrier (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
qlnx_txq_doorbell_wr32(qlnx_host_t *ha, void *reg_addr, uint32_t value)
{
	struct ecore_dev	*cdev;
	uint32_t		offset;

	cdev = &ha->cdev;
		
	offset = (uint32_t)((uint8_t *)reg_addr - (uint8_t *)ha->pci_dbells);

	bus_write_4(ha->pci_dbells, offset, value);
	bus_barrier(ha->pci_reg,  0, 0, BUS_SPACE_BARRIER_READ);
	bus_barrier(ha->pci_dbells,  0, 0, BUS_SPACE_BARRIER_READ);

	return;
}