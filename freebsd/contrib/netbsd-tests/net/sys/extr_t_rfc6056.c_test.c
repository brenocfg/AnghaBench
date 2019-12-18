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
struct sockaddr_storage {int ai_family; int ss_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ss_len; } ;
struct sockaddr {int dummy; } ;
struct addrinfo {int ai_family; int ss_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ss_len; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  hello ;
typedef  int /*<<< orphan*/  al ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int IPV6_PORTALGO ; 
 int IP_PORTALGO ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  abort () ; 
 int bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int close (int) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct sockaddr_storage*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct sockaddr_storage*,struct sockaddr_storage**) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int send (int,char const*,int,int /*<<< orphan*/ ) ; 
 int sendto (int,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setsockopt (int,int,int,int*,int) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test(const char *hostname, const char *service, int family, int al)
{
	static const char hello[] = "hello\n";
	int s, error, proto, option;
	struct sockaddr_storage ss;
	struct addrinfo hints, *res;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = SOCK_DGRAM;

	switch (family) {
	case AF_INET:
		proto = IPPROTO_IP;
		option = IP_PORTALGO;
		break;
	case AF_INET6:
		proto = IPPROTO_IPV6;
		option = IPV6_PORTALGO;
		break;
	default:
		abort();
	}

	error = getaddrinfo(hostname, service, &hints, &res);
	if (error)
		errx(EXIT_FAILURE, "Cannot get address for %s (%s)",
		    hostname, gai_strerror(error));
	
	s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (s == -1)
		err(EXIT_FAILURE, "socket");
	
	if (setsockopt(s, proto, option, &al, sizeof(al)) == -1)
		err(EXIT_FAILURE, "setsockopt");

	memset(&ss, 0, sizeof(ss));
	ss.ss_len = res->ai_addrlen;
	ss.ss_family = res->ai_family;

	if (bind(s, (struct sockaddr *)&ss, ss.ss_len) == -1)
		err(EXIT_FAILURE, "bind");
		
	if (sendto(s, hello, sizeof(hello) - 1, 0,
	    res->ai_addr, res->ai_addrlen) == -1)
		err(EXIT_FAILURE, "sendto");

	if (close(s) == -1)
		err(EXIT_FAILURE, "close");

	s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (s == -1)
		err(EXIT_FAILURE, "socket");

	if (setsockopt(s, proto, option, &al, sizeof(al)) == -1)
		err(EXIT_FAILURE, "setsockopt");

	if (connect(s, res->ai_addr, res->ai_addrlen) == -1)
		err(EXIT_FAILURE, "connect");

	if (send(s, hello, sizeof(hello) - 1, 0) == -1)
		err(EXIT_FAILURE, "send");

	if (close(s) == -1)
		err(EXIT_FAILURE, "close");

	freeaddrinfo(res);
}