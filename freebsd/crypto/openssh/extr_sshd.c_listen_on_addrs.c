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
struct listenaddr {char* rdomain; struct addrinfo* addrs; } ;
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  strport ;
typedef  int /*<<< orphan*/  socksize ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  ntop ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 size_t MAX_LISTEN_SOCKS ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SSH_LISTEN_BACKLOG ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  debug (char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int /*<<< orphan*/  getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int* listen_socks ; 
 int /*<<< orphan*/  logit (char*,char*,char*,char*,char*) ; 
 size_t num_listen_socks ; 
 int set_nonblock (int) ; 
 int set_rdomain (int,char*) ; 
 int /*<<< orphan*/  set_reuseaddr (int) ; 
 int /*<<< orphan*/  sock_set_v6only (int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_gai_strerror (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
listen_on_addrs(struct listenaddr *la)
{
	int ret, listen_sock;
	struct addrinfo *ai;
	char ntop[NI_MAXHOST], strport[NI_MAXSERV];
	int socksize;
	socklen_t len;

	for (ai = la->addrs; ai; ai = ai->ai_next) {
		if (ai->ai_family != AF_INET && ai->ai_family != AF_INET6)
			continue;
		if (num_listen_socks >= MAX_LISTEN_SOCKS)
			fatal("Too many listen sockets. "
			    "Enlarge MAX_LISTEN_SOCKS");
		if ((ret = getnameinfo(ai->ai_addr, ai->ai_addrlen,
		    ntop, sizeof(ntop), strport, sizeof(strport),
		    NI_NUMERICHOST|NI_NUMERICSERV)) != 0) {
			error("getnameinfo failed: %.100s",
			    ssh_gai_strerror(ret));
			continue;
		}
		/* Create socket for listening. */
		listen_sock = socket(ai->ai_family, ai->ai_socktype,
		    ai->ai_protocol);
		if (listen_sock < 0) {
			/* kernel may not support ipv6 */
			verbose("socket: %.100s", strerror(errno));
			continue;
		}
		if (set_nonblock(listen_sock) == -1) {
			close(listen_sock);
			continue;
		}
		if (fcntl(listen_sock, F_SETFD, FD_CLOEXEC) == -1) {
			verbose("socket: CLOEXEC: %s", strerror(errno));
			close(listen_sock);
			continue;
		}
		/* Socket options */
		set_reuseaddr(listen_sock);
		if (la->rdomain != NULL &&
		    set_rdomain(listen_sock, la->rdomain) == -1) {
			close(listen_sock);
			continue;
		}

		/* Only communicate in IPv6 over AF_INET6 sockets. */
		if (ai->ai_family == AF_INET6)
			sock_set_v6only(listen_sock);

		debug("Bind to port %s on %s.", strport, ntop);

		len = sizeof(socksize);
		getsockopt(listen_sock, SOL_SOCKET, SO_RCVBUF, &socksize, &len);
		debug("Server TCP RWIN socket size: %d", socksize);

		/* Bind the socket to the desired port. */
		if (bind(listen_sock, ai->ai_addr, ai->ai_addrlen) < 0) {
			error("Bind to port %s on %s failed: %.200s.",
			    strport, ntop, strerror(errno));
			close(listen_sock);
			continue;
		}
		listen_socks[num_listen_socks] = listen_sock;
		num_listen_socks++;

		/* Start listening on the port. */
		if (listen(listen_sock, SSH_LISTEN_BACKLOG) < 0)
			fatal("listen on [%s]:%s: %.100s",
			    ntop, strport, strerror(errno));
		logit("Server listening on %s port %s%s%s.",
		    ntop, strport,
		    la->rdomain == NULL ? "" : " rdomain ",
		    la->rdomain == NULL ? "" : la->rdomain);
	}
}