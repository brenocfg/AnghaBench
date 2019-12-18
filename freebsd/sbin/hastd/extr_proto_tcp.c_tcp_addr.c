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
struct sockaddr_storage {int dummy; } ;
struct addrinfo {int ai_flags; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  portstr ;
typedef  int /*<<< orphan*/  iporhost ;
typedef  int intmax_t ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int AI_ADDRCONFIG ; 
 int AI_NUMERICSERV ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  bzero (struct addrinfo*,int) ; 
 int errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int numfromstr (char const*,int,int,int*) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strchr (char const*,char) ; 
 size_t strlcpy (char*,char const*,size_t) ; 
 scalar_t__ strncasecmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int
tcp_addr(const char *addr, int defport, struct sockaddr_storage *sap)
{
	char iporhost[MAXHOSTNAMELEN], portstr[6];
	struct addrinfo hints;
	struct addrinfo *res;
	const char *pp;
	intmax_t port;
	size_t size;
	int error;

	if (addr == NULL)
		return (-1);

	bzero(&hints, sizeof(hints));
	hints.ai_flags = AI_ADDRCONFIG | AI_NUMERICSERV;
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (strncasecmp(addr, "tcp4://", 7) == 0) {
		addr += 7;
		hints.ai_family = PF_INET;
	} else if (strncasecmp(addr, "tcp6://", 7) == 0) {
		addr += 7;
		hints.ai_family = PF_INET6;
	} else if (strncasecmp(addr, "tcp://", 6) == 0) {
		addr += 6;
	} else {
		/*
		 * Because TCP is the default assume IP or host is given without
		 * prefix.
		 */
	}

	/*
	 * Extract optional port.
	 * There are three cases to consider.
	 * 1. hostname with port, eg. freefall.freebsd.org:8457
	 * 2. IPv4 address with port, eg. 192.168.0.101:8457
	 * 3. IPv6 address with port, eg. [fe80::1]:8457
	 * We discover IPv6 address by checking for two colons and if port is
	 * given, the address has to start with [.
	 */
	pp = NULL;
	if (strchr(addr, ':') != strrchr(addr, ':')) {
		if (addr[0] == '[')
			pp = strrchr(addr, ':');
	} else {
		pp = strrchr(addr, ':');
	}
	if (pp == NULL) {
		/* Port not given, use the default. */
		port = defport;
	} else {
		if (numfromstr(pp + 1, 1, 65535, &port) == -1)
			return (errno);
	}
	(void)snprintf(portstr, sizeof(portstr), "%jd", (intmax_t)port);
	/* Extract host name or IP address. */
	if (pp == NULL) {
		size = sizeof(iporhost);
		if (strlcpy(iporhost, addr, size) >= size)
			return (ENAMETOOLONG);
	} else if (addr[0] == '[' && pp[-1] == ']') {
		size = (size_t)(pp - addr - 2 + 1);
		if (size > sizeof(iporhost))
			return (ENAMETOOLONG);
		(void)strlcpy(iporhost, addr + 1, size);
	} else {
		size = (size_t)(pp - addr + 1);
		if (size > sizeof(iporhost))
			return (ENAMETOOLONG);
		(void)strlcpy(iporhost, addr, size);
	}

	error = getaddrinfo(iporhost, portstr, &hints, &res);
	if (error != 0) {
		pjdlog_debug(1, "getaddrinfo(%s, %s) failed: %s.", iporhost,
		    portstr, gai_strerror(error));
		return (EINVAL);
	}
	if (res == NULL)
		return (ENOENT);

	memcpy(sap, res->ai_addr, res->ai_addrlen);

	freeaddrinfo(res);

	return (0);
}