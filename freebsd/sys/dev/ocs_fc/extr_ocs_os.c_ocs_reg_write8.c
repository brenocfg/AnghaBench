#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_4__ {TYPE_2__* reg; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_5__ {int /*<<< orphan*/  bhandle; int /*<<< orphan*/  btag; } ;
typedef  TYPE_2__ ocs_pci_reg_t ;

/* Variables and functions */
 void bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

void
ocs_reg_write8(ocs_t *ocs, uint32_t rset, uint32_t off, uint8_t val)
{
	ocs_pci_reg_t		*reg = NULL;

	reg = &ocs->reg[rset];

	return bus_space_write_1(reg->btag, reg->bhandle, off, val);
}