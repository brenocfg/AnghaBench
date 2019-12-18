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
struct wpa_supplicant {TYPE_1__* global; struct ctrl_iface_priv* ctrl_iface; } ;
struct ctrl_iface_priv {int sock; int /*<<< orphan*/  msg_queue; } ;
struct ctrl_iface_global_priv {int sock; int /*<<< orphan*/  msg_queue; } ;
struct TYPE_2__ {struct ctrl_iface_global_priv* ctrl_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,void (*) (void*,void*),struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  wpas_ctrl_msg_send_pending_global (TYPE_1__*) ; 
 int /*<<< orphan*/  wpas_ctrl_msg_send_pending_iface (struct wpa_supplicant*) ; 

__attribute__((used)) static void wpas_ctrl_msg_queue_timeout(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	struct ctrl_iface_priv *priv;
	struct ctrl_iface_global_priv *gpriv;
	int sock = -1, gsock = -1;

	wpas_ctrl_msg_send_pending_global(wpa_s->global);
	wpas_ctrl_msg_send_pending_iface(wpa_s);

	priv = wpa_s->ctrl_iface;
	if (priv && !dl_list_empty(&priv->msg_queue))
		sock = priv->sock;

	gpriv = wpa_s->global->ctrl_iface;
	if (gpriv && !dl_list_empty(&gpriv->msg_queue))
		gsock = gpriv->sock;

	if (sock > -1 || gsock > -1) {
		/* Continue pending message transmission from a timeout */
		wpa_printf(MSG_MSGDUMP,
			   "CTRL: Had to throttle pending event message transmission for (sock %d gsock %d)",
			   sock, gsock);
		eloop_register_timeout(0, 20000, wpas_ctrl_msg_queue_timeout,
				       wpa_s, NULL);
	}
}