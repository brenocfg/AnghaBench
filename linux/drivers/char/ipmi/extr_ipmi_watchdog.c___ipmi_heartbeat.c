#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kernel_ipmi_msg {int netfn; scalar_t__ data_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  cmd; } ;
struct ipmi_system_interface_addr {scalar_t__ lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_addr {int dummy; } ;
struct TYPE_4__ {scalar_t__* data; } ;
struct TYPE_5__ {TYPE_1__ msg; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_SET_TIMEOUT_NO_HB ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  IPMI_WDOG_RESET_TIMER ; 
 scalar_t__ IPMI_WDOG_TIMER_NOT_INIT_RESP ; 
 scalar_t__ WDOG_TIMEOUT_NONE ; 
 int _ipmi_set_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int ipmi_request_supply_msgs (int /*<<< orphan*/ ,struct ipmi_addr*,int /*<<< orphan*/ ,struct kernel_ipmi_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ ipmi_watchdog_state ; 
 int /*<<< orphan*/  msg_tofree ; 
 int /*<<< orphan*/  msg_wait ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 TYPE_2__ recv_msg ; 
 int /*<<< orphan*/  smi_msg ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_user ; 

__attribute__((used)) static int __ipmi_heartbeat(void)
{
	struct kernel_ipmi_msg msg;
	int rv;
	struct ipmi_system_interface_addr addr;
	int timeout_retries = 0;

restart:
	/*
	 * Don't reset the timer if we have the timer turned off, that
	 * re-enables the watchdog.
	 */
	if (ipmi_watchdog_state == WDOG_TIMEOUT_NONE)
		return 0;

	atomic_set(&msg_tofree, 2);

	addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	addr.channel = IPMI_BMC_CHANNEL;
	addr.lun = 0;

	msg.netfn = 0x06;
	msg.cmd = IPMI_WDOG_RESET_TIMER;
	msg.data = NULL;
	msg.data_len = 0;
	rv = ipmi_request_supply_msgs(watchdog_user,
				      (struct ipmi_addr *) &addr,
				      0,
				      &msg,
				      NULL,
				      &smi_msg,
				      &recv_msg,
				      1);
	if (rv) {
		pr_warn("heartbeat send failure: %d\n", rv);
		return rv;
	}

	/* Wait for the heartbeat to be sent. */
	wait_for_completion(&msg_wait);

	if (recv_msg.msg.data[0] == IPMI_WDOG_TIMER_NOT_INIT_RESP)  {
		timeout_retries++;
		if (timeout_retries > 3) {
			pr_err("Unable to restore the IPMI watchdog's settings, giving up\n");
			rv = -EIO;
			goto out;
		}

		/*
		 * The timer was not initialized, that means the BMC was
		 * probably reset and lost the watchdog information.  Attempt
		 * to restore the timer's info.  Note that we still hold
		 * the heartbeat lock, to keep a heartbeat from happening
		 * in this process, so must say no heartbeat to avoid a
		 * deadlock on this mutex
		 */
		rv = _ipmi_set_timeout(IPMI_SET_TIMEOUT_NO_HB);
		if (rv) {
			pr_err("Unable to send the command to set the watchdog's settings, giving up\n");
			goto out;
		}

		/* Might need a heartbeat send, go ahead and do it. */
		goto restart;
	} else if (recv_msg.msg.data[0] != 0) {
		/*
		 * Got an error in the heartbeat response.  It was already
		 * reported in ipmi_wdog_msg_handler, but we should return
		 * an error here.
		 */
		rv = -EINVAL;
	}

out:
	return rv;
}