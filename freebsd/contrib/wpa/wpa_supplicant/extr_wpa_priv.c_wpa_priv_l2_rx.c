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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_priv_l2 {size_t idx; struct wpa_priv_interface* parent; } ;
struct wpa_priv_interface {int /*<<< orphan*/  fd; int /*<<< orphan*/ * l2_addr_len; int /*<<< orphan*/ * l2_addr; } ;
struct msghdr {int msg_iovlen; int /*<<< orphan*/  msg_namelen; int /*<<< orphan*/ * msg_name; struct iovec* msg_iov; } ;
struct iovec {size_t iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  os_memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_priv_l2_rx(void *ctx, const u8 *src_addr, const u8 *buf,
			   size_t len)
{
	struct wpa_priv_l2 *l2_ctx = ctx;
	struct wpa_priv_interface *iface = l2_ctx->parent;
	struct msghdr msg;
	struct iovec io[2];

	io[0].iov_base = (u8 *) src_addr;
	io[0].iov_len = ETH_ALEN;
	io[1].iov_base = (u8 *) buf;
	io[1].iov_len = len;

	os_memset(&msg, 0, sizeof(msg));
	msg.msg_iov = io;
	msg.msg_iovlen = 2;
	msg.msg_name = &iface->l2_addr[l2_ctx->idx];
	msg.msg_namelen = iface->l2_addr_len[l2_ctx->idx];

	if (sendmsg(iface->fd, &msg, 0) < 0) {
		wpa_printf(MSG_ERROR, "sendmsg(l2 rx): %s", strerror(errno));
	}
}