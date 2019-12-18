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
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_un {scalar_t__ sun_family; int /*<<< orphan*/  sun_path; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sun_path; } ;
struct l2_packet_data {int /*<<< orphan*/  rx_callback_ctx; int /*<<< orphan*/  (* rx_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;TYPE_1__ priv_addr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int recvfrom (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void l2_packet_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct l2_packet_data *l2 = eloop_ctx;
	u8 buf[2300];
	int res;
	struct sockaddr_un from;
	socklen_t fromlen = sizeof(from);

	os_memset(&from, 0, sizeof(from));
	res = recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *) &from,
		       &fromlen);
	if (res < 0) {
		wpa_printf(MSG_ERROR, "l2_packet_receive - recvfrom: %s",
			   strerror(errno));
		return;
	}
	if (res < ETH_ALEN) {
		wpa_printf(MSG_DEBUG, "L2: Too show packet received");
		return;
	}

	if (from.sun_family != AF_UNIX ||
	    os_strncmp(from.sun_path, l2->priv_addr.sun_path,
		       sizeof(from.sun_path)) != 0) {
		wpa_printf(MSG_DEBUG, "L2: Received message from unexpected "
			   "source");
		return;
	}

	l2->rx_callback(l2->rx_callback_ctx, buf, buf + ETH_ALEN,
			res - ETH_ALEN);
}