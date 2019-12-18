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
typedef  int /*<<< orphan*/  val ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  snd ;
typedef  int /*<<< orphan*/  rcv ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  off ;
typedef  int /*<<< orphan*/  mtu ;
typedef  int /*<<< orphan*/  got ;
typedef  int /*<<< orphan*/  action ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 scalar_t__ EACCES ; 
 scalar_t__ EADDRINUSE ; 
 scalar_t__ EADDRNOTAVAIL ; 
 scalar_t__ EAFNOSUPPORT ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOPROTOOPT ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 scalar_t__ EPROTONOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_BINDANY ; 
 int IPV6_MIN_MTU ; 
 int /*<<< orphan*/  IPV6_MTU ; 
 int /*<<< orphan*/  IPV6_USE_MIN_MTU ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  IP_BINDANY ; 
 int /*<<< orphan*/  IP_DONTFRAG ; 
 int /*<<< orphan*/  IP_FREEBIND ; 
 int /*<<< orphan*/  IP_MTU_DISCOVER ; 
 int IP_PMTUDISC_DONT ; 
 int IP_PMTUDISC_OMIT ; 
 int /*<<< orphan*/  IP_TRANSPARENT ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BINDANY ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_RCVBUFFORCE ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int /*<<< orphan*/  SO_REUSEPORT_LB ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  SO_SNDBUFFORCE ; 
 scalar_t__ WSAEACCES ; 
 scalar_t__ WSAEADDRINUSE ; 
 scalar_t__ WSAEADDRNOTAVAIL ; 
 scalar_t__ WSAEAFNOSUPPORT ; 
 scalar_t__ WSAEPROTONOSUPPORT ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_set_nonblock (int) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err_addr (char*,int /*<<< orphan*/ ,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*,...) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int socket (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int systemd_get_activated (int,int,int,struct sockaddr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int verbosity ; 
 int /*<<< orphan*/  wsa_strerror (scalar_t__) ; 

int
create_udp_sock(int family, int socktype, struct sockaddr* addr,
        socklen_t addrlen, int v6only, int* inuse, int* noproto,
	int rcv, int snd, int listen, int* reuseport, int transparent,
	int freebind, int use_systemd)
{
	int s;
#if defined(SO_REUSEADDR) || defined(SO_REUSEPORT) || defined(IPV6_USE_MIN_MTU)  || defined(IP_TRANSPARENT) || defined(IP_BINDANY) || defined(IP_FREEBIND) || defined (SO_BINDANY)
	int on=1;
#endif
#ifdef IPV6_MTU
	int mtu = IPV6_MIN_MTU;
#endif
#if !defined(SO_RCVBUFFORCE) && !defined(SO_RCVBUF)
	(void)rcv;
#endif
#if !defined(SO_SNDBUFFORCE) && !defined(SO_SNDBUF)
	(void)snd;
#endif
#ifndef IPV6_V6ONLY
	(void)v6only;
#endif
#if !defined(IP_TRANSPARENT) && !defined(IP_BINDANY) && !defined(SO_BINDANY)
	(void)transparent;
#endif
#if !defined(IP_FREEBIND)
	(void)freebind;
#endif
#ifdef HAVE_SYSTEMD
	int got_fd_from_systemd = 0;

	if (!use_systemd
	    || (use_systemd
		&& (s = systemd_get_activated(family, socktype, -1, addr,
					      addrlen, NULL)) == -1)) {
#else
	(void)use_systemd;
#endif
	if((s = socket(family, socktype, 0)) == -1) {
		*inuse = 0;
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
		*noproto = 0;
		return -1;
	}
#ifdef HAVE_SYSTEMD
	} else {
		got_fd_from_systemd = 1;
	}
#endif
	if(listen) {
#ifdef SO_REUSEADDR
		if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void*)&on, 
			(socklen_t)sizeof(on)) < 0) {
#ifndef USE_WINSOCK
			log_err("setsockopt(.. SO_REUSEADDR ..) failed: %s",
				strerror(errno));
			if(errno != ENOSYS) {
				close(s);
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
#else
			log_err("setsockopt(.. SO_REUSEADDR ..) failed: %s",
				wsa_strerror(WSAGetLastError()));
			closesocket(s);
			*noproto = 0;
			*inuse = 0;
			return -1;
#endif
		}
#endif /* SO_REUSEADDR */
#ifdef SO_REUSEPORT
#  ifdef SO_REUSEPORT_LB
		/* on FreeBSD 12 we have SO_REUSEPORT_LB that does loadbalance
		 * like SO_REUSEPORT on Linux.  This is what the users want
		 * with the config option in unbound.conf; if we actually
		 * need local address and port reuse they'll also need to
		 * have SO_REUSEPORT set for them, assume it was _LB they want.
		 */
		if (reuseport && *reuseport &&
		    setsockopt(s, SOL_SOCKET, SO_REUSEPORT_LB, (void*)&on,
			(socklen_t)sizeof(on)) < 0) {
#ifdef ENOPROTOOPT
			if(errno != ENOPROTOOPT || verbosity >= 3)
				log_warn("setsockopt(.. SO_REUSEPORT_LB ..) failed: %s",
					strerror(errno));
#endif
			/* this option is not essential, we can continue */
			*reuseport = 0;
		}
#  else /* no SO_REUSEPORT_LB */

		/* try to set SO_REUSEPORT so that incoming
		 * queries are distributed evenly among the receiving threads.
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
#  endif /* SO_REUSEPORT_LB */
#else
		(void)reuseport;
#endif /* defined(SO_REUSEPORT) */
#ifdef IP_TRANSPARENT
		if (transparent &&
		    setsockopt(s, IPPROTO_IP, IP_TRANSPARENT, (void*)&on,
		    (socklen_t)sizeof(on)) < 0) {
			log_warn("setsockopt(.. IP_TRANSPARENT ..) failed: %s",
			strerror(errno));
		}
#elif defined(IP_BINDANY)
		if (transparent &&
		    setsockopt(s, (family==AF_INET6? IPPROTO_IPV6:IPPROTO_IP),
		    (family == AF_INET6? IPV6_BINDANY:IP_BINDANY),
		    (void*)&on, (socklen_t)sizeof(on)) < 0) {
			log_warn("setsockopt(.. IP%s_BINDANY ..) failed: %s",
			(family==AF_INET6?"V6":""), strerror(errno));
		}
#elif defined(SO_BINDANY)
		if (transparent &&
		    setsockopt(s, SOL_SOCKET, SO_BINDANY, (void*)&on,
		    (socklen_t)sizeof(on)) < 0) {
			log_warn("setsockopt(.. SO_BINDANY ..) failed: %s",
			strerror(errno));
		}
#endif /* IP_TRANSPARENT || IP_BINDANY || SO_BINDANY */
	}
#ifdef IP_FREEBIND
	if(freebind &&
	    setsockopt(s, IPPROTO_IP, IP_FREEBIND, (void*)&on,
	    (socklen_t)sizeof(on)) < 0) {
		log_warn("setsockopt(.. IP_FREEBIND ..) failed: %s",
		strerror(errno));
	}
#endif /* IP_FREEBIND */
	if(rcv) {
#ifdef SO_RCVBUF
		int got;
		socklen_t slen = (socklen_t)sizeof(got);
#  ifdef SO_RCVBUFFORCE
		/* Linux specific: try to use root permission to override
		 * system limits on rcvbuf. The limit is stored in 
		 * /proc/sys/net/core/rmem_max or sysctl net.core.rmem_max */
		if(setsockopt(s, SOL_SOCKET, SO_RCVBUFFORCE, (void*)&rcv, 
			(socklen_t)sizeof(rcv)) < 0) {
			if(errno != EPERM) {
#    ifndef USE_WINSOCK
				log_err("setsockopt(..., SO_RCVBUFFORCE, "
					"...) failed: %s", strerror(errno));
				close(s);
#    else
				log_err("setsockopt(..., SO_RCVBUFFORCE, "
					"...) failed: %s", 
					wsa_strerror(WSAGetLastError()));
				closesocket(s);
#    endif
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
#  endif /* SO_RCVBUFFORCE */
			if(setsockopt(s, SOL_SOCKET, SO_RCVBUF, (void*)&rcv, 
				(socklen_t)sizeof(rcv)) < 0) {
#  ifndef USE_WINSOCK
				log_err("setsockopt(..., SO_RCVBUF, "
					"...) failed: %s", strerror(errno));
				close(s);
#  else
				log_err("setsockopt(..., SO_RCVBUF, "
					"...) failed: %s", 
					wsa_strerror(WSAGetLastError()));
				closesocket(s);
#  endif
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
			/* check if we got the right thing or if system
			 * reduced to some system max.  Warn if so */
			if(getsockopt(s, SOL_SOCKET, SO_RCVBUF, (void*)&got, 
				&slen) >= 0 && got < rcv/2) {
				log_warn("so-rcvbuf %u was not granted. "
					"Got %u. To fix: start with "
					"root permissions(linux) or sysctl "
					"bigger net.core.rmem_max(linux) or "
					"kern.ipc.maxsockbuf(bsd) values.",
					(unsigned)rcv, (unsigned)got);
			}
#  ifdef SO_RCVBUFFORCE
		}
#  endif
#endif /* SO_RCVBUF */
	}
	/* first do RCVBUF as the receive buffer is more important */
	if(snd) {
#ifdef SO_SNDBUF
		int got;
		socklen_t slen = (socklen_t)sizeof(got);
#  ifdef SO_SNDBUFFORCE
		/* Linux specific: try to use root permission to override
		 * system limits on sndbuf. The limit is stored in 
		 * /proc/sys/net/core/wmem_max or sysctl net.core.wmem_max */
		if(setsockopt(s, SOL_SOCKET, SO_SNDBUFFORCE, (void*)&snd, 
			(socklen_t)sizeof(snd)) < 0) {
			if(errno != EPERM) {
#    ifndef USE_WINSOCK
				log_err("setsockopt(..., SO_SNDBUFFORCE, "
					"...) failed: %s", strerror(errno));
				close(s);
#    else
				log_err("setsockopt(..., SO_SNDBUFFORCE, "
					"...) failed: %s", 
					wsa_strerror(WSAGetLastError()));
				closesocket(s);
#    endif
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
#  endif /* SO_SNDBUFFORCE */
			if(setsockopt(s, SOL_SOCKET, SO_SNDBUF, (void*)&snd, 
				(socklen_t)sizeof(snd)) < 0) {
#  ifndef USE_WINSOCK
				log_err("setsockopt(..., SO_SNDBUF, "
					"...) failed: %s", strerror(errno));
				close(s);
#  else
				log_err("setsockopt(..., SO_SNDBUF, "
					"...) failed: %s", 
					wsa_strerror(WSAGetLastError()));
				closesocket(s);
#  endif
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
			/* check if we got the right thing or if system
			 * reduced to some system max.  Warn if so */
			if(getsockopt(s, SOL_SOCKET, SO_SNDBUF, (void*)&got, 
				&slen) >= 0 && got < snd/2) {
				log_warn("so-sndbuf %u was not granted. "
					"Got %u. To fix: start with "
					"root permissions(linux) or sysctl "
					"bigger net.core.wmem_max(linux) or "
					"kern.ipc.maxsockbuf(bsd) values.",
					(unsigned)snd, (unsigned)got);
			}
#  ifdef SO_SNDBUFFORCE
		}
#  endif
#endif /* SO_SNDBUF */
	}
	if(family == AF_INET6) {
# if defined(IPV6_V6ONLY)
		if(v6only) {
			int val=(v6only==2)?0:1;
			if (setsockopt(s, IPPROTO_IPV6, IPV6_V6ONLY, 
				(void*)&val, (socklen_t)sizeof(val)) < 0) {
#ifndef USE_WINSOCK
				log_err("setsockopt(..., IPV6_V6ONLY"
					", ...) failed: %s", strerror(errno));
				close(s);
#else
				log_err("setsockopt(..., IPV6_V6ONLY"
					", ...) failed: %s", 
					wsa_strerror(WSAGetLastError()));
				closesocket(s);
#endif
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
		}
# endif
# if defined(IPV6_USE_MIN_MTU)
		/*
		 * There is no fragmentation of IPv6 datagrams
		 * during forwarding in the network. Therefore
		 * we do not send UDP datagrams larger than
		 * the minimum IPv6 MTU of 1280 octets. The
		 * EDNS0 message length can be larger if the
		 * network stack supports IPV6_USE_MIN_MTU.
		 */
		if (setsockopt(s, IPPROTO_IPV6, IPV6_USE_MIN_MTU,
			(void*)&on, (socklen_t)sizeof(on)) < 0) {
#  ifndef USE_WINSOCK
			log_err("setsockopt(..., IPV6_USE_MIN_MTU, "
				"...) failed: %s", strerror(errno));
			close(s);
#  else
			log_err("setsockopt(..., IPV6_USE_MIN_MTU, "
				"...) failed: %s", 
				wsa_strerror(WSAGetLastError()));
			closesocket(s);
#  endif
			*noproto = 0;
			*inuse = 0;
			return -1;
		}
# elif defined(IPV6_MTU)
		/*
		 * On Linux, to send no larger than 1280, the PMTUD is
		 * disabled by default for datagrams anyway, so we set
		 * the MTU to use.
		 */
		if (setsockopt(s, IPPROTO_IPV6, IPV6_MTU,
			(void*)&mtu, (socklen_t)sizeof(mtu)) < 0) {
#  ifndef USE_WINSOCK
			log_err("setsockopt(..., IPV6_MTU, ...) failed: %s", 
				strerror(errno));
			close(s);
#  else
			log_err("setsockopt(..., IPV6_MTU, ...) failed: %s", 
				wsa_strerror(WSAGetLastError()));
			closesocket(s);
#  endif
			*noproto = 0;
			*inuse = 0;
			return -1;
		}
# endif /* IPv6 MTU */
	} else if(family == AF_INET) {
#  if defined(IP_MTU_DISCOVER) && defined(IP_PMTUDISC_DONT)
/* linux 3.15 has IP_PMTUDISC_OMIT, Hannes Frederic Sowa made it so that
 * PMTU information is not accepted, but fragmentation is allowed
 * if and only if the packet size exceeds the outgoing interface MTU
 * (and also uses the interface mtu to determine the size of the packets).
 * So there won't be any EMSGSIZE error.  Against DNS fragmentation attacks.
 * FreeBSD already has same semantics without setting the option. */
		int omit_set = 0;
		int action;
#   if defined(IP_PMTUDISC_OMIT)
		action = IP_PMTUDISC_OMIT;
		if (setsockopt(s, IPPROTO_IP, IP_MTU_DISCOVER, 
			&action, (socklen_t)sizeof(action)) < 0) {

			if (errno != EINVAL) {
				log_err("setsockopt(..., IP_MTU_DISCOVER, IP_PMTUDISC_OMIT...) failed: %s",
					strerror(errno));

#    ifndef USE_WINSOCK
				close(s);
#    else
				closesocket(s);
#    endif
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
		}
		else
		{
		    omit_set = 1;
		}
#   endif
		if (omit_set == 0) {
   			action = IP_PMTUDISC_DONT;
			if (setsockopt(s, IPPROTO_IP, IP_MTU_DISCOVER,
				&action, (socklen_t)sizeof(action)) < 0) {
				log_err("setsockopt(..., IP_MTU_DISCOVER, IP_PMTUDISC_DONT...) failed: %s",
					strerror(errno));
#    ifndef USE_WINSOCK
				close(s);
#    else
				closesocket(s);
#    endif
				*noproto = 0;
				*inuse = 0;
				return -1;
			}
		}
#  elif defined(IP_DONTFRAG)
		int off = 0;
		if (setsockopt(s, IPPROTO_IP, IP_DONTFRAG, 
			&off, (socklen_t)sizeof(off)) < 0) {
			log_err("setsockopt(..., IP_DONTFRAG, ...) failed: %s",
				strerror(errno));
#    ifndef USE_WINSOCK
			close(s);
#    else
			closesocket(s);
#    endif
			*noproto = 0;
			*inuse = 0;
			return -1;
		}
#  endif /* IPv4 MTU */
	}
	if(
#ifdef HAVE_SYSTEMD
		!got_fd_from_systemd &&
#endif
		bind(s, (struct sockaddr*)addr, addrlen) != 0) {
		*noproto = 0;
		*inuse = 0;
#ifndef USE_WINSOCK
#ifdef EADDRINUSE
		*inuse = (errno == EADDRINUSE);
		/* detect freebsd jail with no ipv6 permission */
		if(family==AF_INET6 && errno==EINVAL)
			*noproto = 1;
		else if(errno != EADDRINUSE &&
			!(errno == EACCES && verbosity < 4 && !listen)
#ifdef EADDRNOTAVAIL
			&& !(errno == EADDRNOTAVAIL && verbosity < 4 && !listen)
#endif
			) {
			log_err_addr("can't bind socket", strerror(errno),
				(struct sockaddr_storage*)addr, addrlen);
		}
#endif /* EADDRINUSE */
		close(s);
#else /* USE_WINSOCK */
		if(WSAGetLastError() != WSAEADDRINUSE &&
			WSAGetLastError() != WSAEADDRNOTAVAIL &&
			!(WSAGetLastError() == WSAEACCES && verbosity < 4 && !listen)) {
			log_err_addr("can't bind socket", 
				wsa_strerror(WSAGetLastError()),
				(struct sockaddr_storage*)addr, addrlen);
		}
		closesocket(s);
#endif /* USE_WINSOCK */
		return -1;
	}
	if(!fd_set_nonblock(s)) {
		*noproto = 0;
		*inuse = 0;
#ifndef USE_WINSOCK
		close(s);
#else
		closesocket(s);
#endif
		return -1;
	}
	return s;
}