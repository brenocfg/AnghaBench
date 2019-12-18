#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {TYPE_1__* pqi_reg; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
struct TYPE_6__ {int /*<<< orphan*/  pqi_dev_status; int /*<<< orphan*/  admin_q_config; int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  COND_WAIT (int,int) ; 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int LE_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LE_64 (scalar_t__) ; 
 int /*<<< orphan*/  OS_SLEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_MEM_GET32 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_MEM_GET64 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQISRC_MODE_READY_POLL_INTERVAL ; 
 int PQISRC_PQIMODE_READY_TIMEOUT ; 
 int /*<<< orphan*/  PQISRC_PQI_DEVICE_SIGNATURE ; 
 int /*<<< orphan*/  PQI_ADMINQ_CONFIG ; 
 scalar_t__ PQI_ADMIN_QUEUE_CONF_FUNC_STATUS_IDLE ; 
 int PQI_DEV_STATE_AT_INIT ; 
 int /*<<< orphan*/  PQI_DEV_STATUS ; 
 int /*<<< orphan*/  PQI_SIGNATURE ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int PQI_STATUS_TIMEOUT ; 
 int /*<<< orphan*/  PRINT_PQI_SIGNATURE (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pqisrc_check_pqimode(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_FAILURE;
	int tmo = 0;
	uint64_t signature = 0;

	DBG_FUNC("IN\n");

	/* Check the PQI device signature */
	tmo = PQISRC_PQIMODE_READY_TIMEOUT;
	do {
		signature = LE_64(PCI_MEM_GET64(softs, &softs->pqi_reg->signature, PQI_SIGNATURE));
        
		if (memcmp(&signature, PQISRC_PQI_DEVICE_SIGNATURE,
				sizeof(uint64_t)) == 0) {
			ret = PQI_STATUS_SUCCESS;
			break;
		}
		OS_SLEEP(PQISRC_MODE_READY_POLL_INTERVAL);
	} while (tmo--);

	PRINT_PQI_SIGNATURE(signature);

	if (tmo <= 0) {
		DBG_ERR("PQI Signature is invalid\n");
		ret = PQI_STATUS_TIMEOUT;
		goto err_out;
	}

	tmo = PQISRC_PQIMODE_READY_TIMEOUT;
	/* Check function and status code for the device */
	COND_WAIT((PCI_MEM_GET64(softs, &softs->pqi_reg->admin_q_config,
		PQI_ADMINQ_CONFIG) == PQI_ADMIN_QUEUE_CONF_FUNC_STATUS_IDLE), tmo);
	if (!tmo) {
		DBG_ERR("PQI device is not in IDLE state\n");
		ret = PQI_STATUS_TIMEOUT;
		goto err_out;
	}


	tmo = PQISRC_PQIMODE_READY_TIMEOUT;
	/* Check the PQI device status register */
	COND_WAIT(LE_32(PCI_MEM_GET32(softs, &softs->pqi_reg->pqi_dev_status, PQI_DEV_STATUS)) &
				PQI_DEV_STATE_AT_INIT, tmo);
	if (!tmo) {
		DBG_ERR("PQI Registers are not ready\n");
		ret = PQI_STATUS_TIMEOUT;
		goto err_out;
	}

	DBG_FUNC("OUT\n");
	return ret;
err_out:
	DBG_FUNC("OUT failed\n");
	return ret;
}