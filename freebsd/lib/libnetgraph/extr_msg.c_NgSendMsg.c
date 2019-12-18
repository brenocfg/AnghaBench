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
struct TYPE_2__ {int typecookie; int token; int cmd; scalar_t__ cmdstr; int /*<<< orphan*/  flags; int /*<<< orphan*/  version; } ;
struct ng_mesg {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  NGF_ORIG ; 
 int /*<<< orphan*/  NG_CMDSTRSIZ ; 
 int /*<<< orphan*/  NG_VERSION ; 
 scalar_t__ NgDeliverMsg (int,char const*,struct ng_mesg*,void const*,size_t) ; 
 int atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gMsgId ; 
 int /*<<< orphan*/  memset (struct ng_mesg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

int
NgSendMsg(int cs, const char *path,
	  int cookie, int cmd, const void *args, size_t arglen)
{
	struct ng_mesg msg;

	/* Prepare message header */
	memset(&msg, 0, sizeof(msg));
	msg.header.version = NG_VERSION;
	msg.header.typecookie = cookie;
	msg.header.token = atomic_fetch_add(&gMsgId, 1) & INT_MAX;
	msg.header.flags = NGF_ORIG;
	msg.header.cmd = cmd;
	snprintf((char *)msg.header.cmdstr, NG_CMDSTRSIZ, "cmd%d", cmd);

	/* Deliver message */
	if (NgDeliverMsg(cs, path, &msg, args, arglen) < 0)
		return (-1);
	return (msg.header.token);
}