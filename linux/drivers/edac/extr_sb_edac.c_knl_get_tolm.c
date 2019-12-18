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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  pci_mc_info; } ;
struct sbridge_pvt {TYPE_1__ knl; } ;

/* Variables and functions */
 int GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  KNL_TOLM ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 knl_get_tolm(struct sbridge_pvt *pvt)
{
	u32 reg;

	pci_read_config_dword(pvt->knl.pci_mc_info, KNL_TOLM, &reg);
	return (GET_BITFIELD(reg, 26, 31) << 26) | 0x3ffffff;
}