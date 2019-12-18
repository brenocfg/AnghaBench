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
struct TYPE_2__ {scalar_t__ cmd; scalar_t__* data; } ;
struct ipmi_recv_msg {TYPE_1__ msg; } ;

/* Variables and functions */
 scalar_t__ IPMI_WDOG_RESET_TIMER ; 
 scalar_t__ IPMI_WDOG_TIMER_NOT_INIT_RESP ; 
 int /*<<< orphan*/  ipmi_free_recv_msg (struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void ipmi_wdog_msg_handler(struct ipmi_recv_msg *msg,
				  void                 *handler_data)
{
	if (msg->msg.cmd == IPMI_WDOG_RESET_TIMER &&
			msg->msg.data[0] == IPMI_WDOG_TIMER_NOT_INIT_RESP)
		pr_info("response: The IPMI controller appears to have been reset, will attempt to reinitialize the watchdog timer\n");
	else if (msg->msg.data[0] != 0)
		pr_err("response: Error %x on cmd %x\n",
		       msg->msg.data[0],
		       msg->msg.cmd);

	ipmi_free_recv_msg(msg);
}