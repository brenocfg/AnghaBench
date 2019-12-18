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
typedef  int uintmax_t ;
struct TYPE_3__ {int StatusCode; int TargetAssistFlags; int QueueTag; int ReplyWord; int RelativeOffset; int DataLength; int /*<<< orphan*/  SGL; int /*<<< orphan*/  LUN; } ;
typedef  TYPE_1__* PTR_MSG_TARGET_ASSIST_REQUEST ;
typedef  int /*<<< orphan*/  MSG_REQUEST_HEADER ;

/* Variables and functions */
 scalar_t__ be64dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_dump_sgl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_print_request_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
mpt_print_scsi_target_assist_request(PTR_MSG_TARGET_ASSIST_REQUEST msg)
{

	mpt_print_request_hdr((MSG_REQUEST_HEADER *)msg);
	printf("\tStatusCode    0x%02x\n", msg->StatusCode);
	printf("\tTargetAssist  0x%02x\n", msg->TargetAssistFlags);
	printf("\tQueueTag      0x%04x\n", msg->QueueTag);
	printf("\tReplyWord     0x%08x\n", msg->ReplyWord);
	printf("\tLun           0x%jx\n", (uintmax_t)be64dec(msg->LUN));
	printf("\tRelativeOff   0x%08x\n", msg->RelativeOffset);
	printf("\tDataLength    0x%08x\n", msg->DataLength);
	mpt_dump_sgl(msg->SGL, 0);
}