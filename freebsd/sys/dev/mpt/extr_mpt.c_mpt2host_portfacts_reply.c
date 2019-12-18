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
typedef  int /*<<< orphan*/  MSG_PORT_FACTS_REPLY ;

/* Variables and functions */
 int /*<<< orphan*/  IOCLogInfo ; 
 int /*<<< orphan*/  IOCStatus ; 
 int /*<<< orphan*/  MPT_2_HOST16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaxDevices ; 
 int /*<<< orphan*/  MaxLanBuckets ; 
 int /*<<< orphan*/  MaxPersistentIDs ; 
 int /*<<< orphan*/  MaxPostedCmdBuffers ; 
 int /*<<< orphan*/  MsgContext ; 
 int /*<<< orphan*/  PortSCSIID ; 
 int /*<<< orphan*/  ProtocolFlags ; 
 int /*<<< orphan*/  Reserved ; 
 int /*<<< orphan*/  Reserved1 ; 
 int /*<<< orphan*/  Reserved2 ; 
 int /*<<< orphan*/  Reserved4 ; 
 int /*<<< orphan*/  Reserved5 ; 

void
mpt2host_portfacts_reply(MSG_PORT_FACTS_REPLY *pfp)
{

	MPT_2_HOST16(pfp, Reserved);
	MPT_2_HOST16(pfp, Reserved1);
	MPT_2_HOST32(pfp, MsgContext);
	MPT_2_HOST16(pfp, Reserved2);
	MPT_2_HOST16(pfp, IOCStatus);
	MPT_2_HOST32(pfp, IOCLogInfo);
	MPT_2_HOST16(pfp, MaxDevices);
	MPT_2_HOST16(pfp, PortSCSIID);
	MPT_2_HOST16(pfp, ProtocolFlags);
	MPT_2_HOST16(pfp, MaxPostedCmdBuffers);
	MPT_2_HOST16(pfp, MaxPersistentIDs);
	MPT_2_HOST16(pfp, MaxLanBuckets);
	MPT_2_HOST16(pfp, Reserved4);
	MPT_2_HOST32(pfp, Reserved5);
}