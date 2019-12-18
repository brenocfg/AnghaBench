#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct sockaddr_in6 {int sin_len; int sin6_len; void* sin6_port; int /*<<< orphan*/  sin6_family; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {int sin_len; int sin6_len; void* sin6_port; int /*<<< orphan*/  sin6_family; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EALREADY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/ * SCTP_BASE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 TYPE_1__* curthread ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_over_udp_stop () ; 
 int /*<<< orphan*/  sctp_recv_icmp6_tunneled_packet ; 
 int /*<<< orphan*/  sctp_recv_icmp_tunneled_packet ; 
 int /*<<< orphan*/  sctp_recv_udp_tunneled_packet ; 
 int /*<<< orphan*/  sctp_udp_tunneling_port ; 
 int sobind (int /*<<< orphan*/ *,struct sockaddr*,TYPE_1__*) ; 
 int socreate (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  udp4_tun_socket ; 
 int /*<<< orphan*/  udp6_tun_socket ; 
 int udp_set_kernel_tunneling (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
sctp_over_udp_start(void)
{
	uint16_t port;
	int ret;
#ifdef INET
	struct sockaddr_in sin;
#endif
#ifdef INET6
	struct sockaddr_in6 sin6;
#endif
	/*
	 * This function assumes sysctl caller holds sctp_sysctl_info_lock()
	 * for writting!
	 */
	port = SCTP_BASE_SYSCTL(sctp_udp_tunneling_port);
	if (ntohs(port) == 0) {
		/* Must have a port set */
		return (EINVAL);
	}
#ifdef INET
	if (SCTP_BASE_INFO(udp4_tun_socket) != NULL) {
		/* Already running -- must stop first */
		return (EALREADY);
	}
#endif
#ifdef INET6
	if (SCTP_BASE_INFO(udp6_tun_socket) != NULL) {
		/* Already running -- must stop first */
		return (EALREADY);
	}
#endif
#ifdef INET
	if ((ret = socreate(PF_INET, &SCTP_BASE_INFO(udp4_tun_socket),
	    SOCK_DGRAM, IPPROTO_UDP,
	    curthread->td_ucred, curthread))) {
		sctp_over_udp_stop();
		return (ret);
	}
	/* Call the special UDP hook. */
	if ((ret = udp_set_kernel_tunneling(SCTP_BASE_INFO(udp4_tun_socket),
	    sctp_recv_udp_tunneled_packet,
	    sctp_recv_icmp_tunneled_packet,
	    NULL))) {
		sctp_over_udp_stop();
		return (ret);
	}
	/* Ok, we have a socket, bind it to the port. */
	memset(&sin, 0, sizeof(struct sockaddr_in));
	sin.sin_len = sizeof(struct sockaddr_in);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if ((ret = sobind(SCTP_BASE_INFO(udp4_tun_socket),
	    (struct sockaddr *)&sin, curthread))) {
		sctp_over_udp_stop();
		return (ret);
	}
#endif
#ifdef INET6
	if ((ret = socreate(PF_INET6, &SCTP_BASE_INFO(udp6_tun_socket),
	    SOCK_DGRAM, IPPROTO_UDP,
	    curthread->td_ucred, curthread))) {
		sctp_over_udp_stop();
		return (ret);
	}
	/* Call the special UDP hook. */
	if ((ret = udp_set_kernel_tunneling(SCTP_BASE_INFO(udp6_tun_socket),
	    sctp_recv_udp_tunneled_packet,
	    sctp_recv_icmp6_tunneled_packet,
	    NULL))) {
		sctp_over_udp_stop();
		return (ret);
	}
	/* Ok, we have a socket, bind it to the port. */
	memset(&sin6, 0, sizeof(struct sockaddr_in6));
	sin6.sin6_len = sizeof(struct sockaddr_in6);
	sin6.sin6_family = AF_INET6;
	sin6.sin6_port = htons(port);
	if ((ret = sobind(SCTP_BASE_INFO(udp6_tun_socket),
	    (struct sockaddr *)&sin6, curthread))) {
		sctp_over_udp_stop();
		return (ret);
	}
#endif
	return (0);
}