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
typedef  int u8 ;
struct wpa_driver_privsep_data {scalar_t__ cmd_socket; int /*<<< orphan*/  priv_addr; } ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct msghdr {int msg_iovlen; int msg_namelen; int /*<<< orphan*/ * msg_name; struct iovec* msg_iov; } ;
struct iovec {int* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  os_memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 int recv (scalar_t__,void*,size_t,int /*<<< orphan*/ ) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ sendmsg (scalar_t__,struct msghdr*,int /*<<< orphan*/ ) ; 
 int strerror (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wpa_priv_cmd(struct wpa_driver_privsep_data *drv, int cmd,
			const void *data, size_t data_len,
			void *reply, size_t *reply_len)
{
	struct msghdr msg;
	struct iovec io[2];

	io[0].iov_base = &cmd;
	io[0].iov_len = sizeof(cmd);
	io[1].iov_base = (u8 *) data;
	io[1].iov_len = data_len;

	os_memset(&msg, 0, sizeof(msg));
	msg.msg_iov = io;
	msg.msg_iovlen = data ? 2 : 1;
	msg.msg_name = &drv->priv_addr;
	msg.msg_namelen = sizeof(drv->priv_addr);

	if (sendmsg(drv->cmd_socket, &msg, 0) < 0) {
		wpa_printf(MSG_ERROR, "sendmsg(cmd_socket): %s",
			   strerror(errno));
		return -1;
	}

	if (reply) {
		fd_set rfds;
		struct timeval tv;
		int res;

		FD_ZERO(&rfds);
		FD_SET(drv->cmd_socket, &rfds);
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		res = select(drv->cmd_socket + 1, &rfds, NULL, NULL, &tv);
		if (res < 0 && errno != EINTR) {
			wpa_printf(MSG_ERROR, "select: %s", strerror(errno));
			return -1;
		}

		if (FD_ISSET(drv->cmd_socket, &rfds)) {
			res = recv(drv->cmd_socket, reply, *reply_len, 0);
			if (res < 0) {
				wpa_printf(MSG_ERROR, "recv: %s",
					   strerror(errno));
				return -1;
			}
			*reply_len = res;
		} else {
			wpa_printf(MSG_DEBUG, "PRIVSEP: Timeout while waiting "
				   "for reply (cmd=%d)", cmd);
			return -1;
		}
	}

	return 0;
}