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
struct wpa_supplicant {int /*<<< orphan*/  eapol; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct ctrl_iface_priv {int /*<<< orphan*/  ctrl_dst; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  eapol_sm_notify_ctrl_attached (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int /*<<< orphan*/  os_memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 scalar_t__ os_strncmp (char*,char*,int) ; 
 int recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ sendto (int,char*,size_t,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_supplicant_ctrl_iface_attach (int /*<<< orphan*/ *,struct sockaddr_storage*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_supplicant_ctrl_iface_detach (int /*<<< orphan*/ *,struct sockaddr_storage*,int) ; 
 scalar_t__ wpa_supplicant_ctrl_iface_level (struct ctrl_iface_priv*,struct sockaddr_storage*,int,char*) ; 
 char* wpa_supplicant_ctrl_iface_process (struct wpa_supplicant*,char*,size_t*) ; 
 int wpas_ctrl_iface_reinit (struct wpa_supplicant*,struct ctrl_iface_priv*) ; 
 int /*<<< orphan*/  wpas_ctrl_sock_debug (char*,int,char*,size_t) ; 

__attribute__((used)) static void wpa_supplicant_ctrl_iface_receive(int sock, void *eloop_ctx,
					      void *sock_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	struct ctrl_iface_priv *priv = sock_ctx;
	char buf[4096];
	int res;
	struct sockaddr_storage from;
	socklen_t fromlen = sizeof(from);
	char *reply = NULL, *reply_buf = NULL;
	size_t reply_len = 0;
	int new_attached = 0;

	res = recvfrom(sock, buf, sizeof(buf) - 1, 0,
		       (struct sockaddr *) &from, &fromlen);
	if (res < 0) {
		wpa_printf(MSG_ERROR, "recvfrom(ctrl_iface): %s",
			   strerror(errno));
		return;
	}
	buf[res] = '\0';

	if (os_strcmp(buf, "ATTACH") == 0) {
		if (wpa_supplicant_ctrl_iface_attach(&priv->ctrl_dst, &from,
						     fromlen, 0))
			reply_len = 1;
		else {
			new_attached = 1;
			reply_len = 2;
		}
	} else if (os_strcmp(buf, "DETACH") == 0) {
		if (wpa_supplicant_ctrl_iface_detach(&priv->ctrl_dst, &from,
						     fromlen))
			reply_len = 1;
		else
			reply_len = 2;
	} else if (os_strncmp(buf, "LEVEL ", 6) == 0) {
		if (wpa_supplicant_ctrl_iface_level(priv, &from, fromlen,
						    buf + 6))
			reply_len = 1;
		else
			reply_len = 2;
	} else {
		reply_buf = wpa_supplicant_ctrl_iface_process(wpa_s, buf,
							      &reply_len);
		reply = reply_buf;

		/*
		 * There could be some password/key material in the command, so
		 * clear the buffer explicitly now that it is not needed
		 * anymore.
		 */
		os_memset(buf, 0, res);
	}

	if (!reply && reply_len == 1) {
		reply = "FAIL\n";
		reply_len = 5;
	} else if (!reply && reply_len == 2) {
		reply = "OK\n";
		reply_len = 3;
	}

	if (reply) {
		wpas_ctrl_sock_debug("ctrl_sock-sendto", sock, reply,
				     reply_len);
		if (sendto(sock, reply, reply_len, 0, (struct sockaddr *) &from,
			   fromlen) < 0) {
			int _errno = errno;
			wpa_dbg(wpa_s, MSG_DEBUG,
				"ctrl_iface sendto failed: %d - %s",
				_errno, strerror(_errno));
			if (_errno == ENOBUFS || _errno == EAGAIN) {
				/*
				 * The socket send buffer could be full. This
				 * may happen if client programs are not
				 * receiving their pending messages. Close and
				 * reopen the socket as a workaround to avoid
				 * getting stuck being unable to send any new
				 * responses.
				 */
				sock = wpas_ctrl_iface_reinit(wpa_s, priv);
				if (sock < 0) {
					wpa_dbg(wpa_s, MSG_DEBUG, "Failed to reinitialize ctrl_iface socket");
				}
			}
			if (new_attached) {
				wpa_dbg(wpa_s, MSG_DEBUG, "Failed to send response to ATTACH - detaching");
				new_attached = 0;
				wpa_supplicant_ctrl_iface_detach(
					&priv->ctrl_dst, &from, fromlen);
			}
		}
	}
	os_free(reply_buf);

	if (new_attached)
		eapol_sm_notify_ctrl_attached(wpa_s->eapol);
}