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
typedef  int uint32_t ;
struct al_hal_eth_adapter {scalar_t__ udma_id; int /*<<< orphan*/  name; int /*<<< orphan*/  ec_ints_base; int /*<<< orphan*/  mac_ints_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_INT_GROUP_A ; 
 int /*<<< orphan*/  AL_INT_GROUP_B ; 
 int /*<<< orphan*/  AL_INT_GROUP_C ; 
 int /*<<< orphan*/  AL_INT_GROUP_D ; 
 int EPERM ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,...) ; 
 int al_iofic_read_cause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int al_eth_ec_mac_isr(struct al_hal_eth_adapter *adapter)
{
	uint32_t cause;
	al_dbg("[%s]: ethernet interrupts handler\n", adapter->name);

	// only udma 0 allowed to init ec
	if (adapter->udma_id != 0)
		return -EPERM;

	/* read ec cause */
	cause = al_iofic_read_cause(adapter->ec_ints_base, AL_INT_GROUP_A);
	al_dbg("[%s]: ethernet group A cause 0x%08x\n", adapter->name, cause);
	if (cause & 1)
	{
		cause = al_iofic_read_cause(adapter->mac_ints_base, AL_INT_GROUP_A);
		al_dbg("[%s]: mac group A cause 0x%08x\n", adapter->name, cause);

		cause = al_iofic_read_cause(adapter->mac_ints_base, AL_INT_GROUP_B);
		al_dbg("[%s]: mac group B cause 0x%08x\n", adapter->name, cause);

		cause = al_iofic_read_cause(adapter->mac_ints_base, AL_INT_GROUP_C);
		al_dbg("[%s]: mac group C cause 0x%08x\n", adapter->name, cause);

		cause = al_iofic_read_cause(adapter->mac_ints_base, AL_INT_GROUP_D);
		al_dbg("[%s]: mac group D cause 0x%08x\n", adapter->name, cause);
	}
	cause = al_iofic_read_cause(adapter->ec_ints_base, AL_INT_GROUP_B);
	al_dbg("[%s]: ethernet group B cause 0x%08x\n", adapter->name, cause);
	cause = al_iofic_read_cause(adapter->ec_ints_base, AL_INT_GROUP_C);
	al_dbg("[%s]: ethernet group C cause 0x%08x\n", adapter->name, cause);
	cause = al_iofic_read_cause(adapter->ec_ints_base, AL_INT_GROUP_D);
	al_dbg("[%s]: ethernet group D cause 0x%08x\n", adapter->name, cause);

	return 0;
}