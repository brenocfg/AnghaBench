#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 int FDD ; 
#define  SLI4_ASIC_TYPE_BE3 129 
#define  SLI4_ASIC_TYPE_SKYHAWK 128 
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 scalar_t__ SLI4_IF_TYPE_LANCER_FC_ETH ; 
 unsigned int SLI4_PHYDEV_CONTROL_DD ; 
 unsigned int SLI4_PHYDEV_CONTROL_FRST ; 
 int /*<<< orphan*/  SLI4_REG_PHYSDEV_CONTROL ; 
 int /*<<< orphan*/  SLI4_REG_SLIPORT_CONTROL ; 
 int /*<<< orphan*/  SLI4_REG_SW_UE_CSR1 ; 
 int /*<<< orphan*/  SLI4_REG_SW_UE_CSR2 ; 
 unsigned int SLI4_SLIPORT_CONTROL_FDD ; 
 unsigned int SLI4_SLIPORT_CONTROL_IP ; 
 int /*<<< orphan*/  SLI4_SW_UE_REG ; 
 unsigned int ocs_config_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_config_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ sli_get_asic_type (TYPE_1__*) ; 
 scalar_t__ sli_get_if_type (TYPE_1__*) ; 
 int /*<<< orphan*/  sli_reg_write (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 

int32_t sli_raise_ue(sli4_t *sli4, uint8_t dump)
{
#define FDD 2
	if (SLI4_IF_TYPE_BE3_SKH_PF == sli_get_if_type(sli4)) {
		switch(sli_get_asic_type(sli4)) {
		case SLI4_ASIC_TYPE_BE3: {
			sli_reg_write(sli4, SLI4_REG_SW_UE_CSR1, 0xffffffff);
			sli_reg_write(sli4, SLI4_REG_SW_UE_CSR2, 0);
			break;
		}
		case SLI4_ASIC_TYPE_SKYHAWK: {
			uint32_t value;
			value = ocs_config_read32(sli4->os, SLI4_SW_UE_REG);
			ocs_config_write32(sli4->os, SLI4_SW_UE_REG, (value | (1U << 24)));
			break;
		}
		default:
			ocs_log_test(sli4->os, "invalid asic type %d\n", sli_get_asic_type(sli4));
			return -1;
		}
	} else if (SLI4_IF_TYPE_LANCER_FC_ETH == sli_get_if_type(sli4)) {	
		if (dump == FDD) {
			sli_reg_write(sli4, SLI4_REG_SLIPORT_CONTROL, SLI4_SLIPORT_CONTROL_FDD | SLI4_SLIPORT_CONTROL_IP);
		} else {
			uint32_t value = SLI4_PHYDEV_CONTROL_FRST;
			if (dump == 1) {
				value |= SLI4_PHYDEV_CONTROL_DD;
			}
			sli_reg_write(sli4, SLI4_REG_PHYSDEV_CONTROL, value);
		}
	} else {
		ocs_log_test(sli4->os, "invalid iftype=%d\n", sli_get_if_type(sli4));
		return -1;
	}
	return 0;
}