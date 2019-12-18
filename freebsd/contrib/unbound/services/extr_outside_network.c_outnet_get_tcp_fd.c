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
typedef  int /*<<< orphan*/  tcp_mss ;
struct sockaddr_storage {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_MAXSEG ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ addr_is_ip6 (struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_err_addr (char*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

int
outnet_get_tcp_fd(struct sockaddr_storage* addr, socklen_t addrlen, int tcp_mss)
{
	int s;
#ifdef SO_REUSEADDR
	int on = 1;
#endif
#ifdef INET6
	if(addr_is_ip6(addr, addrlen))
		s = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);
	else
#endif
		s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(s == -1) {
#ifndef USE_WINSOCK
		log_err_addr("outgoing tcp: socket", strerror(errno),
			addr, addrlen);
#else
		log_err_addr("outgoing tcp: socket", 
			wsa_strerror(WSAGetLastError()), addr, addrlen);
#endif
		return -1;
	}

#ifdef SO_REUSEADDR
	if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void*)&on,
		(socklen_t)sizeof(on)) < 0) {
		verbose(VERB_ALGO, "outgoing tcp:"
			" setsockopt(.. SO_REUSEADDR ..) failed");
	}
#endif

	if(tcp_mss > 0) {
#if defined(IPPROTO_TCP) && defined(TCP_MAXSEG)
		if(setsockopt(s, IPPROTO_TCP, TCP_MAXSEG,
			(void*)&tcp_mss, (socklen_t)sizeof(tcp_mss)) < 0) {
			verbose(VERB_ALGO, "outgoing tcp:"
				" setsockopt(.. TCP_MAXSEG ..) failed");
		}
#else
		verbose(VERB_ALGO, "outgoing tcp:"
			" setsockopt(TCP_MAXSEG) unsupported");
#endif /* defined(IPPROTO_TCP) && defined(TCP_MAXSEG) */
	}

	return s;
}