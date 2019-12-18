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
struct hv_kvp_msg {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  hv_kvp_selinfo; int /*<<< orphan*/  dev_sema; struct hv_kvp_msg daemon_kvp_msg; struct hv_kvp_msg* host_kvp_msg; } ;
typedef  TYPE_1__ hv_kvp_sc ;

/* Variables and functions */
 int /*<<< orphan*/  hv_kvp_convert_hostmsg_to_usermsg (struct hv_kvp_msg*,struct hv_kvp_msg*) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hv_kvp_send_msg_to_daemon(hv_kvp_sc *sc)
{
	struct hv_kvp_msg *hmsg = sc->host_kvp_msg;
	struct hv_kvp_msg *umsg = &sc->daemon_kvp_msg;

	/* Prepare kvp_msg to be sent to user */
	hv_kvp_convert_hostmsg_to_usermsg(hmsg, umsg);

	/* Send the msg to user via function deamon_read - setting sema */
	sema_post(&sc->dev_sema);

	/* We should wake up the daemon, in case it's doing poll() */
	selwakeup(&sc->hv_kvp_selinfo);
}