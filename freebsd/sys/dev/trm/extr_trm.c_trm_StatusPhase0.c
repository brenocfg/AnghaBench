#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  SRBState; int /*<<< orphan*/  TargetStatus; } ;
typedef  TYPE_1__* PSRB ;
typedef  int /*<<< orphan*/  PACB ;

/* Variables and functions */
 int /*<<< orphan*/  DO_DATALATCH ; 
 int /*<<< orphan*/  PH_BUS_FREE ; 
 int /*<<< orphan*/  SCMD_MSGACCEPT ; 
 int /*<<< orphan*/  SRB_COMPLETED ; 
 int /*<<< orphan*/  TRMREG_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRMREG_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRMREG_SCSI_FIFO ; 
 int /*<<< orphan*/  trm_reg_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trm_reg_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
trm_StatusPhase0(PACB pACB, PSRB pSRB, u_int16_t *pscsi_status)
{

	pSRB->TargetStatus = trm_reg_read8(TRMREG_SCSI_FIFO);
	pSRB->SRBState = SRB_COMPLETED;
	*pscsi_status = PH_BUS_FREE;  
	/*.. initial phase*/
	trm_reg_write16(DO_DATALATCH, TRMREG_SCSI_CONTROL);
	/* it's important for atn stop */
	/*
	 * SCSI cammand 
	 */
	trm_reg_write8(SCMD_MSGACCEPT, TRMREG_SCSI_COMMAND);
}