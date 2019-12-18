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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  DSL_DEV_MeiError_t ;
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_TO_MEI_MAILBOX ; 
 int /*<<< orphan*/  ARC_TO_MEI_MSGAV ; 
 int /*<<< orphan*/  DSL_DEV_MEI_ERR_SUCCESS ; 
 int /*<<< orphan*/  IFX_MEI_DMARead (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IFX_MEI_LongWordWriteOffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ME_ARC2ME_STAT ; 

__attribute__((used)) static DSL_DEV_MeiError_t
IFX_MEI_MailboxRead (DSL_DEV_Device_t * pDev, u16 * msgdestbuffer,
			   u16 msgsize)
{
	DSL_DEV_MeiError_t meiMailboxError = DSL_DEV_MEI_ERR_SUCCESS;
	//      Read from mailbox
	meiMailboxError =
		IFX_MEI_DMARead (pDev, ARC_TO_MEI_MAILBOX, (u32 *) msgdestbuffer, msgsize / 2);

	//      Notify arc that mailbox read completed
	IFX_MEI_LongWordWriteOffset (pDev, (u32) ME_ARC2ME_STAT, ARC_TO_MEI_MSGAV);

	return meiMailboxError;
}