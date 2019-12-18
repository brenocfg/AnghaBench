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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int cmv_waiting; } ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_FAILURE ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 TYPE_1__* DSL_DEV_PRIVATE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IFX_MEI_DMAWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  IFX_MEI_EMSG (char*,int) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordReadOffset (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  MEI_TO_ARC_MAILBOX ; 
 int /*<<< orphan*/  MEI_TO_ARC_MAILBOXR ; 
 int MEI_TO_ARC_MSGAV ; 
 scalar_t__ ME_ME2ARC_INT ; 
 int WHILE_DELAY ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_MailboxWrite (DSL_DEV_Device_t * pDev, u16 * msgsrcbuffer,
			    u16 msgsize)
{
	int i;
	u32 arc_mailbox_status = 0x0;
	u32 temp = 0;
	DSL_DEV_MeiError_t meiMailboxError = DSL_DEV_MEI_ERR_SUCCESS;

	//      Write to mailbox
	meiMailboxError =
		IFX_MEI_DMAWrite (pDev, MEI_TO_ARC_MAILBOX, (u32 *) msgsrcbuffer, msgsize / 2);
	meiMailboxError =
		IFX_MEI_DMAWrite (pDev, MEI_TO_ARC_MAILBOXR, (u32 *) (&temp), 1);

	//      Notify arc that mailbox write completed
	DSL_DEV_PRIVATE(pDev)->cmv_waiting = 1;
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_ME2ARC_INT, MEI_TO_ARC_MSGAV);

	i = 0;
	while (i < WHILE_DELAY) {	// wait for ARC to clear the bit
		IFX_MEI_LongWordReadOffset (pDev, (u32) ME_ME2ARC_INT, &arc_mailbox_status);
		if ((arc_mailbox_status & MEI_TO_ARC_MSGAV) != MEI_TO_ARC_MSGAV)
			break;
		i++;
		if (i == WHILE_DELAY) {
			IFX_MEI_EMSG (">>> Timeout waiting for ARC to clear MEI_TO_ARC_MSGAV!!!"
			      " MEI_TO_ARC message size = %d DWORDs <<<\n", msgsize/2);
			meiMailboxError = DSL_DEV_MEI_ERR_FAILURE;
		}
	}

	return meiMailboxError;
}