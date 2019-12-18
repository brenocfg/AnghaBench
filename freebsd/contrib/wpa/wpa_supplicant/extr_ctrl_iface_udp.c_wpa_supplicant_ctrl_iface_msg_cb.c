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
struct wpa_supplicant {TYPE_2__* ctrl_iface; int /*<<< orphan*/ * ifname; TYPE_1__* global; } ;
struct ctrl_iface_global_priv {scalar_t__ ctrl_dst; int /*<<< orphan*/  sock; } ;
typedef  enum wpa_msg_type { ____Placeholder_wpa_msg_type } wpa_msg_type ;
struct TYPE_4__ {scalar_t__ ctrl_dst; int /*<<< orphan*/  sock; } ;
struct TYPE_3__ {struct ctrl_iface_global_priv* ctrl_iface; } ;

/* Variables and functions */
 int WPA_MSG_NO_GLOBAL ; 
 int WPA_MSG_ONLY_GLOBAL ; 
 int WPA_MSG_PER_INTERFACE ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_send (struct wpa_supplicant*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int,char const*,size_t) ; 

__attribute__((used)) static void wpa_supplicant_ctrl_iface_msg_cb(void *ctx, int level,
					     enum wpa_msg_type type,
					     const char *txt, size_t len)
{
	struct wpa_supplicant *wpa_s = ctx;

	if (!wpa_s)
		return;

	if (type != WPA_MSG_NO_GLOBAL && wpa_s->global->ctrl_iface) {
		struct ctrl_iface_global_priv *priv = wpa_s->global->ctrl_iface;

		if (priv->ctrl_dst) {
			wpa_supplicant_ctrl_iface_send(
				wpa_s,
				type != WPA_MSG_PER_INTERFACE ?
				NULL : wpa_s->ifname,
				priv->sock, &priv->ctrl_dst, level, txt, len);
		}
	}

	if (type == WPA_MSG_ONLY_GLOBAL || !wpa_s->ctrl_iface)
		return;

	wpa_supplicant_ctrl_iface_send(wpa_s, NULL, wpa_s->ctrl_iface->sock,
				       &wpa_s->ctrl_iface->ctrl_dst,
				       level, txt, len);
}