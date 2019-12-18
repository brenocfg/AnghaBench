#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_addrlen; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_family; } ;
struct TYPE_10__ {int /*<<< orphan*/  sa; } ;
typedef  TYPE_1__ sockaddr_u ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF (TYPE_1__ const*) ; 
 int /*<<< orphan*/  AI_ADDRCONFIG ; 
 int /*<<< orphan*/  AI_CANONNAME ; 
 int EAI_BADFLAGS ; 
 int EAI_NODATA ; 
 int EAI_NONAME ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  LIB_BUFLENGTH ; 
 int /*<<< orphan*/  LIB_GETBUF (char*) ; 
 int NI_DGRAM ; 
 int NI_NAMEREQD ; 
 int /*<<< orphan*/  SOCKLEN (TYPE_1__ const*) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ SOCK_EQ (TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRACE (int,char*) ; 
 int /*<<< orphan*/  ZERO (struct addrinfo) ; 
 int /*<<< orphan*/  ZERO_SOCK (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char const*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ getnameinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 size_t min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int socket_errno () ; 
 char* stoa (TYPE_1__ const*) ; 

const char *
socktohost(
	const sockaddr_u *sock
	)
{
	const char		svc[] = "ntp";
	char *			pbuf;
	char *			pliar;
	int			gni_flags;
	struct addrinfo		hints;
	struct addrinfo *	alist;
	struct addrinfo *	ai;
	sockaddr_u		addr;
	size_t			octets;
	int			a_info;
	int			saved_errno;

	saved_errno = socket_errno();

	/* reverse the address to purported DNS name */
	LIB_GETBUF(pbuf);
	gni_flags = NI_DGRAM | NI_NAMEREQD;
	if (getnameinfo(&sock->sa, SOCKLEN(sock), pbuf, LIB_BUFLENGTH,
			NULL, 0, gni_flags)) {
		errno = saved_errno;
		return stoa(sock);	/* use address */
	}

	TRACE(1, ("%s reversed to %s\n", stoa(sock), pbuf));

	/*
	 * Resolve the reversed name and make sure the reversed address
	 * is among the results.
	 */
	ZERO(hints);
	hints.ai_family = AF(sock);
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = 0;
	alist = NULL;

	a_info = getaddrinfo(pbuf, svc, &hints, &alist);
	if (a_info == EAI_NONAME
#ifdef EAI_NODATA
	    || a_info == EAI_NODATA
#endif
	   ) {
		hints.ai_flags = AI_CANONNAME;
#ifdef AI_ADDRCONFIG
		hints.ai_flags |= AI_ADDRCONFIG;
#endif
		a_info = getaddrinfo(pbuf, svc, &hints, &alist);	
	}
#ifdef AI_ADDRCONFIG
	/* Some older implementations don't like AI_ADDRCONFIG. */
	if (a_info == EAI_BADFLAGS) {
		hints.ai_flags &= ~AI_ADDRCONFIG;
		a_info = getaddrinfo(pbuf, svc, &hints, &alist);	
	}
#endif
	if (a_info)
		goto forward_fail;

	INSIST(alist != NULL);

	for (ai = alist; ai != NULL; ai = ai->ai_next) {
		/*
		 * Make a convenience sockaddr_u copy from ai->ai_addr
		 * because casting from sockaddr * to sockaddr_u * is
		 * risking alignment problems on platforms where
		 * sockaddr_u has stricter alignment than sockaddr,
		 * such as sparc.
		 */
		ZERO_SOCK(&addr);
		octets = min(sizeof(addr), ai->ai_addrlen);
		memcpy(&addr, ai->ai_addr, octets);
		if (SOCK_EQ(sock, &addr))
			break;
	}
	freeaddrinfo(alist);

	if (ai != NULL) {
		errno = saved_errno;
		return pbuf;	/* forward check passed */
	}

    forward_fail:
	TRACE(1, ("%s forward check lookup fail: %s\n", pbuf,
		  gai_strerror(a_info)));
	LIB_GETBUF(pliar);
	snprintf(pliar, LIB_BUFLENGTH, "%s (%s)", stoa(sock), pbuf);

	errno = saved_errno;
	return pliar;
}