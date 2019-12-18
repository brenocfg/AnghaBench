#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int ctrl_in_pqi_mode; TYPE_3__* pqi_reg; TYPE_1__* ioa_reg; scalar_t__ pqi_reset_quiesce_allowed; } ;
typedef  TYPE_4__ pqisrc_softstate_t ;
struct TYPE_12__ {int /*<<< orphan*/  reset_action; int /*<<< orphan*/  reset_type; } ;
struct TYPE_15__ {int /*<<< orphan*/  all_bits; TYPE_2__ bits; } ;
typedef  TYPE_5__ pqi_reset_reg_t ;
struct TYPE_13__ {int /*<<< orphan*/  dev_reset; } ;
struct TYPE_11__ {int /*<<< orphan*/  host_to_ioa_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*,int) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int /*<<< orphan*/  LEGACY_SIS_IDBR ; 
 int /*<<< orphan*/  LE_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_MEM_GET32 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_MEM_PUT32 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQI_DEV_RESET ; 
 int /*<<< orphan*/  PQI_RESET_ACTION_RESET ; 
 int /*<<< orphan*/  PQI_RESET_TYPE_HARD_RESET ; 
 int PQI_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SIS_PQI_RESET_QUIESCE ; 
 int pqisrc_sis_wait_for_db_bit_to_clear (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int pqisrc_wait_for_pqi_reset_completion (TYPE_4__*) ; 

int pqi_reset(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	uint32_t val = 0;
	pqi_reset_reg_t pqi_reset_reg;

	DBG_FUNC("IN\n");

	if (true == softs->ctrl_in_pqi_mode) { 
	
		if (softs->pqi_reset_quiesce_allowed) {
			val = PCI_MEM_GET32(softs, &softs->ioa_reg->host_to_ioa_db,
					LEGACY_SIS_IDBR);
			val |= SIS_PQI_RESET_QUIESCE;
			PCI_MEM_PUT32(softs, &softs->ioa_reg->host_to_ioa_db,
					LEGACY_SIS_IDBR, LE_32(val));
			ret = pqisrc_sis_wait_for_db_bit_to_clear(softs, SIS_PQI_RESET_QUIESCE);
			if (ret) {
				DBG_ERR("failed with error %d during quiesce\n", ret);
				return ret;
			}
		}

		pqi_reset_reg.all_bits = 0;
		pqi_reset_reg.bits.reset_type = PQI_RESET_TYPE_HARD_RESET;
		pqi_reset_reg.bits.reset_action = PQI_RESET_ACTION_RESET;

		PCI_MEM_PUT32(softs, &softs->pqi_reg->dev_reset, PQI_DEV_RESET,
			LE_32(pqi_reset_reg.all_bits));

		ret = pqisrc_wait_for_pqi_reset_completion(softs);
		if (ret) {
			DBG_ERR("PQI reset timed out: ret = %d!\n", ret);
			return ret;
		}
	}
	softs->ctrl_in_pqi_mode = false;
	DBG_FUNC("OUT\n");
	return ret;
}