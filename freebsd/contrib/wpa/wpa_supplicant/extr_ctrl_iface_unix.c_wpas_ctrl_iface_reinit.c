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
struct wpa_supplicant {int dummy; } ;
struct ctrl_iface_priv {int sock; scalar_t__ android_control_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (int) ; 
 int wpas_ctrl_iface_open_sock (struct wpa_supplicant*,struct ctrl_iface_priv*) ; 

__attribute__((used)) static int wpas_ctrl_iface_reinit(struct wpa_supplicant *wpa_s,
				  struct ctrl_iface_priv *priv)
{
	int res;

	if (priv->sock <= 0)
		return -1;

	/*
	 * On Android, the control socket being used may be the socket
	 * that is created when wpa_supplicant is started as a /init.*.rc
	 * service. Such a socket is maintained as a key-value pair in
	 * Android's environment. Closing this control socket would leave us
	 * in a bad state with an invalid socket descriptor.
	 */
	if (priv->android_control_socket)
		return priv->sock;

	eloop_unregister_read_sock(priv->sock);
	close(priv->sock);
	priv->sock = -1;
	res = wpas_ctrl_iface_open_sock(wpa_s, priv);
	if (res < 0)
		return -1;
	return priv->sock;
}