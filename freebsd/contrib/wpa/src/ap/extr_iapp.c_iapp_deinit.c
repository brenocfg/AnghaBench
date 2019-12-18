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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct ip_mreqn {scalar_t__ imr_ifindex; TYPE_1__ imr_address; int /*<<< orphan*/  imr_multiaddr; } ;
struct iapp_data {scalar_t__ udp_sock; scalar_t__ packet_sock; int /*<<< orphan*/  multicast; } ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IP_DROP_MEMBERSHIP ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  eloop_unregister_read_sock (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  os_free (struct iapp_data*) ; 
 int /*<<< orphan*/  os_memset (struct ip_mreqn*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_mreqn*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void iapp_deinit(struct iapp_data *iapp)
{
	struct ip_mreqn mreq;

	if (iapp == NULL)
		return;

	if (iapp->udp_sock >= 0) {
		os_memset(&mreq, 0, sizeof(mreq));
		mreq.imr_multiaddr = iapp->multicast;
		mreq.imr_address.s_addr = INADDR_ANY;
		mreq.imr_ifindex = 0;
		if (setsockopt(iapp->udp_sock, SOL_IP, IP_DROP_MEMBERSHIP,
			       &mreq, sizeof(mreq)) < 0) {
			wpa_printf(MSG_INFO, "iapp_deinit - setsockopt[UDP,IP_DEL_MEMBERSHIP]: %s",
				   strerror(errno));
		}

		eloop_unregister_read_sock(iapp->udp_sock);
		close(iapp->udp_sock);
	}
	if (iapp->packet_sock >= 0) {
		eloop_unregister_read_sock(iapp->packet_sock);
		close(iapp->packet_sock);
	}
	os_free(iapp);
}