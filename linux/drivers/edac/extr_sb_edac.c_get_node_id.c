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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sbridge_pvt {int /*<<< orphan*/  pci_br0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BITFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SAD_CONTROL ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 get_node_id(struct sbridge_pvt *pvt)
{
	u32 reg;
	pci_read_config_dword(pvt->pci_br0, SAD_CONTROL, &reg);
	return GET_BITFIELD(reg, 0, 2);
}