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
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  qlen ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  mss ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ EAFNOSUPPORT ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOPROTOOPT ; 
 scalar_t__ EPERM ; 
 scalar_t__ EPROTONOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPV6_BINDANY ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  IP_BINDANY ; 
 int /*<<< orphan*/  IP_FREEBIND ; 
 int /*<<< orphan*/  IP_TRANSPARENT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BINDANY ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int /*<<< orphan*/  TCP_BACKLOG ; 
 int /*<<< orphan*/  TCP_FASTOPEN ; 
 int /*<<< orphan*/  TCP_MAXSEG ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ WSAEAFNOSUPPORT ; 
 scalar_t__ WSAEPROTONOSUPPORT ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ bind (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_set_nonblock (int) ; 
 int listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err_addr (char*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*,...) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int systemd_get_activated (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  verbose_print_addr (struct addrinfo*) ; 
 int verbosity ; 
 int /*<<< orphan*/  wsa_strerror (scalar_t__) ; 

int
create_tcp_accept_sock(struct addrinfo *addr, int v6only, int* noproto,
	int* reuseport, int transparent, int mss, int freebind, int use_systemd)
{
	int s;
#if defined(SO_REUSEADDR) || defined(SO_REUSEPORT) || defined(IPV6_V6ONLY) || defined(IP_TRANSPARENT) || defined(IP_BINDANY) || defined(IP_FREEBIND) || defined(SO_BINDANY)
	int on = 1;
#endif
#ifdef HAVE_SYSTEMD
	int got_fd_from_systemd = 0;
#endif
#ifdef USE_TCP_FASTOPEN
	int qlen;
#endif
#if !defined(IP_TRANSPARENT) && !defined(IP_BINDANY) && !defined(SO_BINDANY)
	(void)transparent;
#endif
#if !defined(IP_FREEBIND)
	(void)freebind;
#endif
	verbose_print_addr(addr);
	*noproto = 0;
#ifdef HAVE_SYSTEMD
	if (!use_systemd ||
	    (use_systemd
	     && (s = systemd_get_activated(addr->ai_family, addr->ai_socktype, 1,
					   addr->ai_addr, addr->ai_addrlen,
					   NULL)) == -1)) {
#else
	(void)use_systemd;
#endif
	if((s = socket(addr->ai_family, addr->ai_socktype, 0)) == -1) {
#ifndef USE_WINSOCK
		if(errno == EAFNOSUPPORT || errno == EPROTONOSUPPORT) {
			*noproto = 1;
			return -1;
		}
		log_err("can't create socket: %s", strerror(errno));
#else
		if(WSAGetLastError() == WSAEAFNOSUPPORT ||
			WSAGetLastError() == WSAEPROTONOSUPPORT) {
			*noproto = 1;
			return -1;
		}
		log_err("can't create socket: %s", 
			wsa_strerror(WSAGetLastError()));
#endif
		return -1;
	}
	if (mss > 0) {
#if defined(IPPROTO_TCP) && defined(TCP_MAXSEG)
		if(setsockopt(s, IPPROTO_TCP, TCP_MAXSEG, (void*)&mss,
			(socklen_t)sizeof(mss)) < 0) {
			#ifndef USE_WINSOCK
			log_err(" setsockopt(.. TCP_MAXSEG ..) failed: %s",
				strerror(errno));
			#else
			log_err(" setsockopt(.. TCP_MAXSEG ..) failed: %s",
				wsa_strerror(WSAGetLastError()));
			#endif
		} else {
			verbose(VERB_ALGO,
				" tcp socket mss set to %d", mss);
		}
#else
		log_warn(" setsockopt(TCP_MAXSEG) unsupported");
#endif /* defined(IPPROTO_TCP) && defined(TCP_MAXSEG) */
	}
#ifdef HAVE_SYSTEMD
	} else {
		got_fd_from_systemd = 1;
    }
#endif
#ifdef SO_REUSEADDR
	if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void*)&on, 
		(socklen_t)sizeof(on)) < 0) {
#ifndef USE_WINSOCK
		log_err("setsockopt(.. SO_REUSEADDR ..) failed: %s",
			strerror(errno));
		close(s);
#else
		log_err("setsockopt(.. SO_REUSEADDR ..) failed: %s",
			wsa_strerror(WSAGetLastError()));
		closesocket(s);
#endif
		return -1;
	}
#endif /* SO_REUSEADDR */
#ifdef IP_FREEBIND
	if (freebind && setsockopt(s, IPPROTO_IP, IP_FREEBIND, (void*)&on,
	    (socklen_t)sizeof(on)) < 0) {
		log_warn("setsockopt(.. IP_FREEBIND ..) failed: %s",
		strerror(errno));
	}
#endif /* IP_FREEBIND */
#ifdef SO_REUSEPORT
	/* try to set SO_REUSEPORT so that incoming
	 * connections are distributed evenly among the receiving threads.
	 * Each thread must have its own socket bound to the same port,
	 * with SO_REUSEPORT set on each socket.
	 */
	if (reuseport && *reuseport &&
		setsockopt(s, SOL_SOCKET, SO_REUSEPORT, (void*)&on,
		(socklen_t)sizeof(on)) < 0) {
#ifdef ENOPROTOOPT
		if(errno != ENOPROTOOPT || verbosity >= 3)
			log_warn("setsockopt(.. SO_REUSEPORT ..) failed: %s",
				strerror(errno));
#endif
		/* this option is not essential, we can continue */
		*reuseport = 0;
	}
#else
	(void)reuseport;
#endif /* defined(SO_REUSEPORT) */
#if defined(IPV6_V6ONLY)
	if(addr->ai_family == AF_INET6 && v6only) {
		if(setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, 
			(void*)&on, (socklen_t)sizeof(on)) < 0) {
#ifndef USE_WINSOCK
			log_err("setsockopt(..., IPV6_V6ONLY, ...) failed: %s",
				strerror(errno));
			close(s);
#else
			log_err("setsockopt(..., IPV6_V6ONLY, ...) failed: %s",
				wsa_strerror(WSAGetLastError()));
			closesocket(s);
#endif
			return -1;
		}
	}
#else
	(void)v6only;
#endif /* IPV6_V6ONLY */
#ifdef IP_TRANSPARENT
	if (transparent &&
	    setsockopt(s, IPPROTO_IP, IP_TRANSPARENT, (void*)&on,
	    (socklen_t)sizeof(on)) < 0) {
		log_warn("setsockopt(.. IP_TRANSPARENT ..) failed: %s",
			strerror(errno));
	}
#elif defined(IP_BINDANY)
	if (transparent &&
	    setsockopt(s, (addr->ai_family==AF_INET6? IPPROTO_IPV6:IPPROTO_IP),
	    (addr->ai_family == AF_INET6? IPV6_BINDANY:IP_BINDANY),
	    (void*)&on, (socklen_t)sizeof(on)) < 0) {
		log_warn("setsockopt(.. IP%s_BINDANY ..) failed: %s",
		(addr->ai_family==AF_INET6?"V6":""), strerror(errno));
	}
#elif defined(SO_BINDANY)
	if (transparent &&
	    setsockopt(s, SOL_SOCKET, SO_BINDANY, (void*)&on, (socklen_t)
	    sizeof(on)) < 0) {
		log_warn("setsockopt(.. SO_BINDANY ..) failed: %s",
		strerror(errno));
	}
#endif /* IP_TRANSPARENT || IP_BINDANY || SO_BINDANY */
	if(
#ifdef HAVE_SYSTEMD
		!got_fd_from_systemd &&
#endif
        bind(s, addr->ai_addr, addr->ai_addrlen) != 0) {
#ifndef USE_WINSOCK
		/* detect freebsd jail with no ipv6 permission */
		if(addr->ai_family==AF_INET6 && errno==EINVAL)
			*noproto = 1;
		else {
			log_err_addr("can't bind socket", strerror(errno),
				(struct sockaddr_storage*)addr->ai_addr,
				addr->ai_addrlen);
		}
		close(s);
#else
		log_err_addr("can't bind socket", 
			wsa_strerror(WSAGetLastError()),
			(struct sockaddr_storage*)addr->ai_addr,
			addr->ai_addrlen);
		closesocket(s);
#endif
		return -1;
	}
	if(!fd_set_nonblock(s)) {
#ifndef USE_WINSOCK
		close(s);
#else
		closesocket(s);
#endif
		return -1;
	}
	if(listen(s, TCP_BACKLOG) == -1) {
#ifndef USE_WINSOCK
		log_err("can't listen: %s", strerror(errno));
		close(s);
#else
		log_err("can't listen: %s", wsa_strerror(WSAGetLastError()));
		closesocket(s);
#endif
		return -1;
	}
#ifdef USE_TCP_FASTOPEN
	/* qlen specifies how many outstanding TFO requests to allow. Limit is a defense
	   against IP spoofing attacks as suggested in RFC7413 */
#ifdef __APPLE__
	/* OS X implementation only supports qlen of 1 via this call. Actual
	   value is configured by the net.inet.tcp.fastopen_backlog kernel parm. */
	qlen = 1;
#else
	/* 5 is recommended on linux */
	qlen = 5;
#endif
	if ((setsockopt(s, IPPROTO_TCP, TCP_FASTOPEN, &qlen, 
		  sizeof(qlen))) == -1 ) {
#ifdef ENOPROTOOPT
		/* squelch ENOPROTOOPT: freebsd server mode with kernel support
		   disabled, except when verbosity enabled for debugging */
		if(errno != ENOPROTOOPT || verbosity >= 3) {
#endif
		  if(errno == EPERM) {
		  	log_warn("Setting TCP Fast Open as server failed: %s ; this could likely be because sysctl net.inet.tcp.fastopen.enabled, net.inet.tcp.fastopen.server_enable, or net.ipv4.tcp_fastopen is disabled", strerror(errno));
		  } else {
		  	log_err("Setting TCP Fast Open as server failed: %s", strerror(errno));
		  }
#ifdef ENOPROTOOPT
		}
#endif
	}
#endif
	return s;
}