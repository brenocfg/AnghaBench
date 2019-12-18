#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Word; } ;
struct TYPE_6__ {int /*<<< orphan*/  HostPageBufferSGE; } ;
typedef  TYPE_1__ MSG_IOC_FACTS_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  CurReplyFrameSize ; 
 int /*<<< orphan*/  CurrentHostMfaHighAddr ; 
 int /*<<< orphan*/  CurrentSenseBufferHighAddr ; 
 int /*<<< orphan*/  FWImageSize ; 
 TYPE_5__ FWVersion ; 
 int /*<<< orphan*/  GlobalCredits ; 
 int /*<<< orphan*/  HeaderVersion ; 
 int /*<<< orphan*/  HighPriorityQueueDepth ; 
 int /*<<< orphan*/  IOCCapabilities ; 
 int /*<<< orphan*/  IOCExceptions ; 
 int /*<<< orphan*/  IOCLogInfo ; 
 int /*<<< orphan*/  IOCStatus ; 
 int /*<<< orphan*/  MPT_2_HOST16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPT_2_HOST32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MsgContext ; 
 int /*<<< orphan*/  MsgVersion ; 
 int /*<<< orphan*/  ProductID ; 
 int /*<<< orphan*/  ReplyFifoHostSignalingAddr ; 
 int /*<<< orphan*/  ReplyQueueDepth ; 
 int /*<<< orphan*/  RequestFrameSize ; 
 int /*<<< orphan*/  Reserved2 ; 
 int /*<<< orphan*/  Reserved_0101_FWVersion ; 
 int /*<<< orphan*/  mpt2host_sge_simple_union (int /*<<< orphan*/ *) ; 

void
mpt2host_iocfacts_reply(MSG_IOC_FACTS_REPLY *rp)
{

	MPT_2_HOST16(rp, MsgVersion);
	MPT_2_HOST16(rp, HeaderVersion);
	MPT_2_HOST32(rp, MsgContext);
	MPT_2_HOST16(rp, IOCExceptions);
	MPT_2_HOST16(rp, IOCStatus);
	MPT_2_HOST32(rp, IOCLogInfo);
	MPT_2_HOST16(rp, ReplyQueueDepth);
	MPT_2_HOST16(rp, RequestFrameSize);
	MPT_2_HOST16(rp, Reserved_0101_FWVersion);
	MPT_2_HOST16(rp, ProductID);
	MPT_2_HOST32(rp, CurrentHostMfaHighAddr);
	MPT_2_HOST16(rp, GlobalCredits);
	MPT_2_HOST32(rp, CurrentSenseBufferHighAddr);
	MPT_2_HOST16(rp, CurReplyFrameSize);
	MPT_2_HOST32(rp, FWImageSize);
	MPT_2_HOST32(rp, IOCCapabilities);
	MPT_2_HOST32(rp, FWVersion.Word);
	MPT_2_HOST16(rp, HighPriorityQueueDepth);
	MPT_2_HOST16(rp, Reserved2);
	mpt2host_sge_simple_union(&rp->HostPageBufferSGE);
	MPT_2_HOST32(rp, ReplyFifoHostSignalingAddr);
}