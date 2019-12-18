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
struct wpa_supplicant {struct ctrl_iface_priv* ctrl_iface; int /*<<< orphan*/ * ifname; TYPE_1__* global; } ;
struct ctrl_iface_priv {scalar_t__ throttle_count; int /*<<< orphan*/  ctrl_dst; int /*<<< orphan*/  sock; int /*<<< orphan*/  msg_queue; } ;
struct ctrl_iface_global_priv {scalar_t__ throttle_count; int /*<<< orphan*/  ctrl_dst; int /*<<< orphan*/  sock; int /*<<< orphan*/  msg_queue; } ;
typedef  enum wpa_msg_type { ____Placeholder_wpa_msg_type } wpa_msg_type ;
struct TYPE_2__ {struct ctrl_iface_global_priv* ctrl_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int WPA_MSG_NO_GLOBAL ; 
 int WPA_MSG_ONLY_GLOBAL ; 
 int WPA_MSG_PER_INTERFACE ; 
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_send (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*,size_t,struct ctrl_iface_priv*,struct ctrl_iface_global_priv*) ; 
 scalar_t__ wpas_ctrl_iface_throttle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_ctrl_msg_queue (int /*<<< orphan*/ *,struct wpa_supplicant*,int,int,char const*,size_t) ; 
 int /*<<< orphan*/  wpas_ctrl_msg_queue_limit (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wpa_supplicant_ctrl_iface_msg_cb(void *ctx, int level,
					     enum wpa_msg_type type,
					     const char *txt, size_t len)
{
	struct wpa_supplicant *wpa_s = ctx;
	struct ctrl_iface_priv *priv;
	struct ctrl_iface_global_priv *gpriv;

	if (wpa_s == NULL)
		return;

	gpriv = wpa_s->global->ctrl_iface;

	if (type != WPA_MSG_NO_GLOBAL && gpriv &&
	    !dl_list_empty(&gpriv->ctrl_dst)) {
		if (!dl_list_empty(&gpriv->msg_queue) ||
		    wpas_ctrl_iface_throttle(gpriv->sock)) {
			if (gpriv->throttle_count == 0) {
				wpa_printf(MSG_MSGDUMP,
					   "CTRL: Had to throttle global event message for sock %d",
					   gpriv->sock);
			}
			gpriv->throttle_count++;
			wpas_ctrl_msg_queue_limit(gpriv->throttle_count,
						  &gpriv->msg_queue);
			wpas_ctrl_msg_queue(&gpriv->msg_queue, wpa_s, level,
					    type, txt, len);
		} else {
			if (gpriv->throttle_count) {
				wpa_printf(MSG_MSGDUMP,
					   "CTRL: Had to throttle %u global event message(s) for sock %d",
					   gpriv->throttle_count, gpriv->sock);
			}
			gpriv->throttle_count = 0;
			wpa_supplicant_ctrl_iface_send(
				wpa_s,
				type != WPA_MSG_PER_INTERFACE ?
				NULL : wpa_s->ifname,
				gpriv->sock, &gpriv->ctrl_dst, level,
				txt, len, NULL, gpriv);
		}
	}

	priv = wpa_s->ctrl_iface;

	if (type != WPA_MSG_ONLY_GLOBAL && priv) {
		if (!dl_list_empty(&priv->msg_queue) ||
		    wpas_ctrl_iface_throttle(priv->sock)) {
			if (priv->throttle_count == 0) {
				wpa_printf(MSG_MSGDUMP,
					   "CTRL: Had to throttle event message for sock %d",
					   priv->sock);
			}
			priv->throttle_count++;
			wpas_ctrl_msg_queue_limit(priv->throttle_count,
						  &priv->msg_queue);
			wpas_ctrl_msg_queue(&priv->msg_queue, wpa_s, level,
					    type, txt, len);
		} else {
			if (priv->throttle_count) {
				wpa_printf(MSG_MSGDUMP,
					   "CTRL: Had to throttle %u event message(s) for sock %d",
					   priv->throttle_count, priv->sock);
			}
			priv->throttle_count = 0;
			wpa_supplicant_ctrl_iface_send(wpa_s, NULL, priv->sock,
						       &priv->ctrl_dst, level,
						       txt, len, priv, NULL);
		}
	}
}