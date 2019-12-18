#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct msghdr {int dummy; } ;
struct TYPE_3__ {int msg_num; } ;
struct TYPE_4__ {TYPE_1__ ipc_msg; } ;

/* Variables and functions */
 TYPE_2__ uc_cfg ; 
 int /*<<< orphan*/  uc_dbgmsg (char*,int) ; 
 scalar_t__ uc_message_send (int,struct msghdr*) ; 

int
uc_message_sendn(int fd, struct msghdr *msghdr)
{
	u_int i;

	for (i = 1; i <= uc_cfg.ipc_msg.msg_num; ++i) {
		uc_dbgmsg("message #%u", i);
		if (uc_message_send(fd, msghdr) < 0)
			return (-1);
	}
	return (0);
}