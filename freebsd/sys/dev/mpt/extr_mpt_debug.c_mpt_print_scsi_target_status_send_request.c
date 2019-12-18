#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uintmax_t ;
struct TYPE_8__ {int StatusCode; int StatusFlags; int QueueTag; int ReplyWord; int /*<<< orphan*/  StatusDataSGE; int /*<<< orphan*/  LUN; } ;
struct TYPE_6__ {int /*<<< orphan*/  Simple; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__ SGE_IO_UNION ;
typedef  TYPE_3__ MSG_TARGET_STATUS_SEND_REQUEST ;
typedef  int /*<<< orphan*/  MSG_REQUEST_HEADER ;

/* Variables and functions */
 scalar_t__ be64dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_dump_sgl (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_print_request_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
mpt_print_scsi_target_status_send_request(MSG_TARGET_STATUS_SEND_REQUEST *msg)
{
	SGE_IO_UNION x;

	mpt_print_request_hdr((MSG_REQUEST_HEADER *)msg);
	printf("\tStatusCode    0x%02x\n", msg->StatusCode);
	printf("\tStatusFlags   0x%02x\n", msg->StatusFlags);
	printf("\tQueueTag      0x%04x\n", msg->QueueTag);
	printf("\tReplyWord     0x%08x\n", msg->ReplyWord);
	printf("\tLun           0x%jx\n", (uintmax_t)be64dec(msg->LUN));
	x.u.Simple = msg->StatusDataSGE;
	mpt_dump_sgl(&x, 0);
}