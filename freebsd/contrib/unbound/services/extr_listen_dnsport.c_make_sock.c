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
struct sockaddr {int dummy; } ;
struct addrinfo {int ai_socktype; scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EAI_NONAME ; 
 int EAI_SYSTEM ; 
 int SOCK_DGRAM ; 
 int create_tcp_accept_sock (struct addrinfo*,int,int*,int*,int,int,int,int) ; 
 int create_udp_sock (scalar_t__,int,struct sockaddr*,int /*<<< orphan*/ ,int,int*,int*,int,int,int,int*,int,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose_print_addr (struct addrinfo*) ; 

__attribute__((used)) static int
make_sock(int stype, const char* ifname, const char* port, 
	struct addrinfo *hints, int v6only, int* noip6, size_t rcv, size_t snd,
	int* reuseport, int transparent, int tcp_mss, int freebind, int use_systemd)
{
	struct addrinfo *res = NULL;
	int r, s, inuse, noproto;
	hints->ai_socktype = stype;
	*noip6 = 0;
	if((r=getaddrinfo(ifname, port, hints, &res)) != 0 || !res) {
#ifdef USE_WINSOCK
		if(r == EAI_NONAME && hints->ai_family == AF_INET6){
			*noip6 = 1; /* 'Host not found' for IP6 on winXP */
			return -1;
		}
#endif
		log_err("node %s:%s getaddrinfo: %s %s", 
			ifname?ifname:"default", port, gai_strerror(r),
#ifdef EAI_SYSTEM
			r==EAI_SYSTEM?(char*)strerror(errno):""
#else
			""
#endif
		);
		return -1;
	}
	if(stype == SOCK_DGRAM) {
		verbose_print_addr(res);
		s = create_udp_sock(res->ai_family, res->ai_socktype,
			(struct sockaddr*)res->ai_addr, res->ai_addrlen,
			v6only, &inuse, &noproto, (int)rcv, (int)snd, 1,
			reuseport, transparent, freebind, use_systemd);
		if(s == -1 && inuse) {
			log_err("bind: address already in use");
		} else if(s == -1 && noproto && hints->ai_family == AF_INET6){
			*noip6 = 1;
		}
	} else	{
		s = create_tcp_accept_sock(res, v6only, &noproto, reuseport,
			transparent, tcp_mss, freebind, use_systemd);
		if(s == -1 && noproto && hints->ai_family == AF_INET6){
			*noip6 = 1;
		}
	}
	freeaddrinfo(res);
	return s;
}