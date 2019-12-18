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
struct eeh_pe {int config_addr; int addr; TYPE_1__* phb; } ;
struct TYPE_2__ {int /*<<< orphan*/  buid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUID_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUID_LO (int /*<<< orphan*/ ) ; 
 int EEH_STATE_DMA_ACTIVE ; 
 int EEH_STATE_MMIO_ACTIVE ; 
 int EEH_STATE_MMIO_ENABLED ; 
 int EEH_STATE_NOT_SUPPORT ; 
 int EEH_STATE_RESET_ACTIVE ; 
 int EEH_STATE_UNAVAILABLE ; 
 scalar_t__ RTAS_UNKNOWN_SERVICE ; 
 scalar_t__ ibm_read_slot_reset_state ; 
 scalar_t__ ibm_read_slot_reset_state2 ; 
 int rtas_call (scalar_t__,int,int,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pseries_eeh_get_state(struct eeh_pe *pe, int *delay)
{
	int config_addr;
	int ret;
	int rets[4];
	int result;

	/* Figure out PE config address if possible */
	config_addr = pe->config_addr;
	if (pe->addr)
		config_addr = pe->addr;

	if (ibm_read_slot_reset_state2 != RTAS_UNKNOWN_SERVICE) {
		ret = rtas_call(ibm_read_slot_reset_state2, 3, 4, rets,
				config_addr, BUID_HI(pe->phb->buid),
				BUID_LO(pe->phb->buid));
	} else if (ibm_read_slot_reset_state != RTAS_UNKNOWN_SERVICE) {
		/* Fake PE unavailable info */
		rets[2] = 0;
		ret = rtas_call(ibm_read_slot_reset_state, 3, 3, rets,
				config_addr, BUID_HI(pe->phb->buid),
				BUID_LO(pe->phb->buid));
	} else {
		return EEH_STATE_NOT_SUPPORT;
	}

	if (ret)
		return ret;

	/* Parse the result out */
	if (!rets[1])
		return EEH_STATE_NOT_SUPPORT;

	switch(rets[0]) {
	case 0:
		result = EEH_STATE_MMIO_ACTIVE |
			 EEH_STATE_DMA_ACTIVE;
		break;
	case 1:
		result = EEH_STATE_RESET_ACTIVE |
			 EEH_STATE_MMIO_ACTIVE  |
			 EEH_STATE_DMA_ACTIVE;
		break;
	case 2:
		result = 0;
		break;
	case 4:
		result = EEH_STATE_MMIO_ENABLED;
		break;
	case 5:
		if (rets[2]) {
			if (delay)
				*delay = rets[2];
			result = EEH_STATE_UNAVAILABLE;
		} else {
			result = EEH_STATE_NOT_SUPPORT;
		}
		break;
	default:
		result = EEH_STATE_NOT_SUPPORT;
	}

	return result;
}