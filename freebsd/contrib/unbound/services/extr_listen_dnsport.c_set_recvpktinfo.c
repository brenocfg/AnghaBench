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
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 int /*<<< orphan*/  IPV6_RECVPKTINFO ; 
 int /*<<< orphan*/  IP_PKTINFO ; 
 int /*<<< orphan*/  IP_RECVDSTADDR ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_recvpktinfo(int s, int family) 
{
#if defined(IPV6_RECVPKTINFO) || defined(IPV6_PKTINFO) || (defined(IP_RECVDSTADDR) && defined(IP_SENDSRCADDR)) || defined(IP_PKTINFO)
	int on = 1;
#else
	(void)s;
#endif
	if(family == AF_INET6) {
#           ifdef IPV6_RECVPKTINFO
		if(setsockopt(s, IPPROTO_IPV6, IPV6_RECVPKTINFO,
			(void*)&on, (socklen_t)sizeof(on)) < 0) {
			log_err("setsockopt(..., IPV6_RECVPKTINFO, ...) failed: %s",
				strerror(errno));
			return 0;
		}
#           elif defined(IPV6_PKTINFO)
		if(setsockopt(s, IPPROTO_IPV6, IPV6_PKTINFO,
			(void*)&on, (socklen_t)sizeof(on)) < 0) {
			log_err("setsockopt(..., IPV6_PKTINFO, ...) failed: %s",
				strerror(errno));
			return 0;
		}
#           else
		log_err("no IPV6_RECVPKTINFO and no IPV6_PKTINFO option, please "
			"disable interface-automatic or do-ip6 in config");
		return 0;
#           endif /* defined IPV6_RECVPKTINFO */

	} else if(family == AF_INET) {
#           ifdef IP_PKTINFO
		if(setsockopt(s, IPPROTO_IP, IP_PKTINFO,
			(void*)&on, (socklen_t)sizeof(on)) < 0) {
			log_err("setsockopt(..., IP_PKTINFO, ...) failed: %s",
				strerror(errno));
			return 0;
		}
#           elif defined(IP_RECVDSTADDR) && defined(IP_SENDSRCADDR)
		if(setsockopt(s, IPPROTO_IP, IP_RECVDSTADDR,
			(void*)&on, (socklen_t)sizeof(on)) < 0) {
			log_err("setsockopt(..., IP_RECVDSTADDR, ...) failed: %s",
				strerror(errno));
			return 0;
		}
#           else
		log_err("no IP_SENDSRCADDR or IP_PKTINFO option, please disable "
			"interface-automatic or do-ip4 in config");
		return 0;
#           endif /* IP_PKTINFO */

	}
	return 1;
}