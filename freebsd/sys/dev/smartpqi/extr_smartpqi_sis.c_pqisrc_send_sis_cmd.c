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
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_1__* ioa_reg; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;
struct TYPE_6__ {int /*<<< orphan*/ * mb; int /*<<< orphan*/  ioa_to_host_db; int /*<<< orphan*/  host_to_ioa_db; int /*<<< orphan*/  ioa_to_host_db_clr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COND_WAIT (int,int) ; 
 int /*<<< orphan*/  DBG_ERR (char*,int) ; 
 int /*<<< orphan*/  DBG_FUNC (char*,...) ; 
 scalar_t__ LEGACY_SIS_IDBR ; 
 scalar_t__ LEGACY_SIS_ODBR_R ; 
 scalar_t__ LEGACY_SIS_SRCV_MAILBOX ; 
 int LE_32 (int) ; 
 int /*<<< orphan*/  OS_BUSYWAIT (int /*<<< orphan*/ ) ; 
 int PCI_MEM_GET32 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PCI_MEM_PUT32 (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int PQI_STATUS_FAILURE ; 
 int PQI_STATUS_SUCCESS ; 
 int PQI_STATUS_TIMEOUT ; 
 int SIS_CMD_COMPLETE ; 
 int SIS_CMD_COMPLETE_TIMEOUT ; 
 int SIS_CMD_STATUS_SUCCESS ; 
 int SIS_CMD_SUBMIT ; 
 int /*<<< orphan*/  SIS_POLL_START_WAIT_TIME ; 

__attribute__((used)) static int pqisrc_send_sis_cmd(pqisrc_softstate_t *softs,
					uint32_t *mb)
{
	int ret = PQI_STATUS_SUCCESS;
	int i = 0;
	uint32_t timeout = SIS_CMD_COMPLETE_TIMEOUT;

	int val;

	DBG_FUNC("IN\n");


	/* Copy Command to mailbox */
	for (i = 0; i < 6; i++)
		PCI_MEM_PUT32(softs, &softs->ioa_reg->mb[i], 
            LEGACY_SIS_SRCV_MAILBOX+i*4, LE_32(mb[i]));
    
	PCI_MEM_PUT32(softs, &softs->ioa_reg->ioa_to_host_db_clr, 
		LEGACY_SIS_ODBR_R, LE_32(0x1000));

	/* Submit the command */
	PCI_MEM_PUT32(softs, &softs->ioa_reg->host_to_ioa_db, 
		LEGACY_SIS_IDBR, LE_32(SIS_CMD_SUBMIT));

#ifdef SIS_POLL_WAIT
	/* Wait for 20  milli sec to poll */
	OS_BUSYWAIT(SIS_POLL_START_WAIT_TIME);
#endif

	val = PCI_MEM_GET32(softs, &softs->ioa_reg->ioa_to_host_db, LEGACY_SIS_ODBR_R);

	DBG_FUNC("val : %x\n",val);
	/* Spin waiting for the command to complete */
	COND_WAIT((PCI_MEM_GET32(softs, &softs->ioa_reg->ioa_to_host_db, LEGACY_SIS_ODBR_R) &
		SIS_CMD_COMPLETE), timeout);
	if (!timeout) {
		DBG_ERR("Sync command %x, timedout\n", mb[0]);
		ret = PQI_STATUS_TIMEOUT;
		goto err_out;
	}
	/* Check command status */
	mb[0] = LE_32(PCI_MEM_GET32(softs, &softs->ioa_reg->mb[0], LEGACY_SIS_SRCV_MAILBOX));

	if (mb[0] != SIS_CMD_STATUS_SUCCESS) {
		DBG_ERR("SIS cmd failed with status = 0x%x\n",
			mb[0]);
		ret = PQI_STATUS_FAILURE;
		goto err_out;
	}

	/* Copy the mailbox back  */
	for (i = 1; i < 6; i++)
		mb[i] =	LE_32(PCI_MEM_GET32(softs, &softs->ioa_reg->mb[i], LEGACY_SIS_SRCV_MAILBOX+i*4));

	DBG_FUNC("OUT\n");
	return ret;

err_out:
	DBG_FUNC("OUT failed\n");
	return ret;
}