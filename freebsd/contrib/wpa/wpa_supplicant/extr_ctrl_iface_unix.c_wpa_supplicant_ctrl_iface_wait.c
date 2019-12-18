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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct ctrl_iface_priv {int sock; int /*<<< orphan*/  ctrl_dst; TYPE_1__* wpa_s; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  eloop_wait_for_read_sock (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_supplicant_ctrl_iface_attach (int /*<<< orphan*/ *,struct sockaddr_storage*,int,int /*<<< orphan*/ ) ; 

void wpa_supplicant_ctrl_iface_wait(struct ctrl_iface_priv *priv)
{
	char buf[256];
	int res;
	struct sockaddr_storage from;
	socklen_t fromlen = sizeof(from);

	if (priv->sock == -1)
		return;

	for (;;) {
		wpa_printf(MSG_DEBUG, "CTRL_IFACE - %s - wait for monitor to "
			   "attach", priv->wpa_s->ifname);
		eloop_wait_for_read_sock(priv->sock);

		res = recvfrom(priv->sock, buf, sizeof(buf) - 1, 0,
			       (struct sockaddr *) &from, &fromlen);
		if (res < 0) {
			wpa_printf(MSG_ERROR, "recvfrom(ctrl_iface): %s",
				   strerror(errno));
			continue;
		}
		buf[res] = '\0';

		if (os_strcmp(buf, "ATTACH") == 0) {
			/* handle ATTACH signal of first monitor interface */
			if (!wpa_supplicant_ctrl_iface_attach(&priv->ctrl_dst,
							      &from, fromlen,
							      0)) {
				if (sendto(priv->sock, "OK\n", 3, 0,
					   (struct sockaddr *) &from, fromlen) <
				    0) {
					wpa_printf(MSG_DEBUG, "ctrl_iface sendto failed: %s",
						   strerror(errno));
				}
				/* OK to continue */
				return;
			} else {
				if (sendto(priv->sock, "FAIL\n", 5, 0,
					   (struct sockaddr *) &from, fromlen) <
				    0) {
					wpa_printf(MSG_DEBUG, "ctrl_iface sendto failed: %s",
						   strerror(errno));
				}
			}
		} else {
			/* return FAIL for all other signals */
			if (sendto(priv->sock, "FAIL\n", 5, 0,
				   (struct sockaddr *) &from, fromlen) < 0) {
				wpa_printf(MSG_DEBUG,
					   "ctrl_iface sendto failed: %s",
					   strerror(errno));
			}
		}
	}
}