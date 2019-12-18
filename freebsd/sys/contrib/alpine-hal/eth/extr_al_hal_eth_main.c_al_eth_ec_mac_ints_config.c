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
struct al_hal_eth_adapter {scalar_t__ udma_id; int /*<<< orphan*/  unit_regs; int /*<<< orphan*/  mac_ints_base; int /*<<< orphan*/  ec_ints_base; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AL_BIT (int) ; 
 int /*<<< orphan*/  AL_INT_GROUP_A ; 
 int /*<<< orphan*/  AL_INT_GROUP_B ; 
 int /*<<< orphan*/  AL_INT_GROUP_C ; 
 int /*<<< orphan*/  AL_INT_GROUP_D ; 
 int EPERM ; 
 int INT_CONTROL_GRP_CLEAR_ON_READ ; 
 int INT_CONTROL_GRP_SET_ON_POSEDGE ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_iofic_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  al_iofic_unmask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int al_eth_ec_mac_ints_config(struct al_hal_eth_adapter *adapter)
{

	al_dbg("eth [%s]: enable ethernet and mac interrupts\n", adapter->name);

	// only udma 0 allowed to init ec
	if (adapter->udma_id != 0)
		return -EPERM;

	/* enable mac ints */
	al_iofic_config(adapter->ec_ints_base, AL_INT_GROUP_A,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);
	al_iofic_config(adapter->ec_ints_base, AL_INT_GROUP_B,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);
	al_iofic_config(adapter->ec_ints_base, AL_INT_GROUP_C,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);
	al_iofic_config(adapter->ec_ints_base, AL_INT_GROUP_D,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);

	/* unmask MAC int */
	al_iofic_unmask(adapter->ec_ints_base, AL_INT_GROUP_A, 8);

	/* enable ec interrupts */
	al_iofic_config(adapter->mac_ints_base, AL_INT_GROUP_A,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);
	al_iofic_config(adapter->mac_ints_base, AL_INT_GROUP_B,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);
	al_iofic_config(adapter->mac_ints_base, AL_INT_GROUP_C,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);
	al_iofic_config(adapter->mac_ints_base, AL_INT_GROUP_D,
		INT_CONTROL_GRP_SET_ON_POSEDGE | INT_CONTROL_GRP_CLEAR_ON_READ);

	/* eee active */
	al_iofic_unmask(adapter->mac_ints_base, AL_INT_GROUP_B, AL_BIT(14));

	al_iofic_unmask(adapter->unit_regs, AL_INT_GROUP_D, AL_BIT(11));
	return 0;
}