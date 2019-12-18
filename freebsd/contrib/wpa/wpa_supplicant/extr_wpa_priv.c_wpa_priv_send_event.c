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
struct wpa_priv_interface {int /*<<< orphan*/  fd; int /*<<< orphan*/  drv_addr_len; int /*<<< orphan*/  drv_addr; } ;
struct msghdr {int msg_iovlen; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/ * msg_name; struct iovec* msg_iov; } ;
struct iovec {int* iov_base; int iov_len; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  os_memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_priv_send_event(struct wpa_priv_interface *iface, int event,
			       const void *data, size_t data_len)
{
	struct msghdr msg;
	struct iovec io[2];

	io[0].iov_base = &event;
	io[0].iov_len = sizeof(event);
	io[1].iov_base = (u8 *) data;
	io[1].iov_len = data_len;

	os_memset(&msg, 0, sizeof(msg));
	msg.msg_iov = io;
	msg.msg_iovlen = data ? 2 : 1;
	msg.msg_name = &iface->drv_addr;
	msg.msg_namelen = iface->drv_addr_len;

	if (sendmsg(iface->fd, &msg, 0) < 0) {
		wpa_printf(MSG_ERROR, "sendmsg(wpas_socket): %s",
			   strerror(errno));
		return -1;
	}

	return 0;
}