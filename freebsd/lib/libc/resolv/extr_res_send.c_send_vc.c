#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct iovec {int dummy; } ;
typedef  TYPE_1__* res_state ;
typedef  int /*<<< orphan*/  on ;
struct TYPE_9__ {int tc; scalar_t__ id; } ;
struct TYPE_8__ {scalar_t__ _vcsock; int _flags; int options; int pfcode; } ;
typedef  int ISC_SOCKLEN_T ;
typedef  TYPE_2__ HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  Aerror (TYPE_1__*,int /*<<< orphan*/ ,char*,int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  DE_CONST (int /*<<< orphan*/  const*,void*) ; 
 int /*<<< orphan*/  Dprint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DprintQ (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
#define  EAFNOSUPPORT 130 
 int ECONNRESET ; 
 int EMSGSIZE ; 
 int ENOTSOCK ; 
#define  EPFNOSUPPORT 129 
#define  EPROTONOSUPPORT 128 
 int HFIXEDSZ ; 
 scalar_t__ INT16SZ ; 
 int PACKETSZ ; 
 int /*<<< orphan*/  Perror (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int RES_DEBUG ; 
 int RES_F_VC ; 
 int RES_PRF_REPLY ; 
 int SOCK_CLOEXEC ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NOSIGPIPE ; 
 scalar_t__ _connect (scalar_t__,struct sockaddr*,int) ; 
 scalar_t__ _getpeername (scalar_t__,struct sockaddr*,int*) ; 
 int _read (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  _setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ _socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ _writev (scalar_t__,struct iovec*,int) ; 
 int errno ; 
 struct iovec evConsIovec (void*,int) ; 
 struct sockaddr* get_nsaddr (TYPE_1__*,int) ; 
 int get_salen (struct sockaddr*) ; 
 scalar_t__ highestFD ; 
 int ns_get16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_put16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  res_nclose (TYPE_1__*) ; 
 int /*<<< orphan*/  sock_eq (struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
send_vc(res_state statp,
	const u_char *buf, int buflen, u_char *ans, int anssiz,
	int *terrno, int ns)
{
	const HEADER *hp = (const HEADER *) buf;
	HEADER *anhp = (HEADER *) ans;
	struct sockaddr *nsap;
	int nsaplen;
	int truncating, connreset, resplen, n;
	struct iovec iov[2];
	u_short len;
	u_char *cp;
	void *tmp;
#ifdef SO_NOSIGPIPE
	int on = 1;
#endif

	nsap = get_nsaddr(statp, ns);
	nsaplen = get_salen(nsap);

	connreset = 0;
 same_ns:
	truncating = 0;

	/* Are we still talking to whom we want to talk to? */
	if (statp->_vcsock >= 0 && (statp->_flags & RES_F_VC) != 0) {
		struct sockaddr_storage peer;
		ISC_SOCKLEN_T size = sizeof peer;

		if (_getpeername(statp->_vcsock,
				(struct sockaddr *)&peer, &size) < 0 ||
		    !sock_eq((struct sockaddr *)&peer, nsap)) {
			res_nclose(statp);
			statp->_flags &= ~RES_F_VC;
		}
	}

	if (statp->_vcsock < 0 || (statp->_flags & RES_F_VC) == 0) {
		if (statp->_vcsock >= 0)
			res_nclose(statp);

		statp->_vcsock = _socket(nsap->sa_family, SOCK_STREAM |
		    SOCK_CLOEXEC, 0);
#if !defined(USE_POLL) && !defined(USE_KQUEUE)
		if (statp->_vcsock > highestFD) {
			res_nclose(statp);
			errno = ENOTSOCK;
		}
#endif
		if (statp->_vcsock < 0) {
			switch (errno) {
			case EPROTONOSUPPORT:
#ifdef EPFNOSUPPORT
			case EPFNOSUPPORT:
#endif
			case EAFNOSUPPORT:
				Perror(statp, stderr, "socket(vc)", errno);
				return (0);
			default:
				*terrno = errno;
				Perror(statp, stderr, "socket(vc)", errno);
				return (-1);
			}
		}
#ifdef SO_NOSIGPIPE
		/*
		 * Disable generation of SIGPIPE when writing to a closed
		 * socket.  Write should return -1 and set errno to EPIPE
		 * instead.
		 *
		 * Push on even if setsockopt(SO_NOSIGPIPE) fails.
		 */
		(void)_setsockopt(statp->_vcsock, SOL_SOCKET, SO_NOSIGPIPE, &on,
				 sizeof(on));
#endif
		errno = 0;
		if (_connect(statp->_vcsock, nsap, nsaplen) < 0) {
			*terrno = errno;
			Aerror(statp, stderr, "connect/vc", errno, nsap,
			    nsaplen);
			res_nclose(statp);
			return (0);
		}
		statp->_flags |= RES_F_VC;
	}

	/*
	 * Send length & message
	 */
	ns_put16((u_short)buflen, (u_char*)&len);
	iov[0] = evConsIovec(&len, INT16SZ);
	DE_CONST(buf, tmp);
	iov[1] = evConsIovec(tmp, buflen);
	if (_writev(statp->_vcsock, iov, 2) != (INT16SZ + buflen)) {
		*terrno = errno;
		Perror(statp, stderr, "write failed", errno);
		res_nclose(statp);
		return (0);
	}
	/*
	 * Receive length & response
	 */
 read_len:
	cp = ans;
	len = INT16SZ;
	while ((n = _read(statp->_vcsock, (char *)cp, (int)len)) > 0) {
		cp += n;
		if ((len -= n) == 0)
			break;
	}
	if (n <= 0) {
		*terrno = errno;
		Perror(statp, stderr, "read failed", errno);
		res_nclose(statp);
		/*
		 * A long running process might get its TCP
		 * connection reset if the remote server was
		 * restarted.  Requery the server instead of
		 * trying a new one.  When there is only one
		 * server, this means that a query might work
		 * instead of failing.  We only allow one reset
		 * per query to prevent looping.
		 */
		if (*terrno == ECONNRESET && !connreset) {
			connreset = 1;
			res_nclose(statp);
			goto same_ns;
		}
		res_nclose(statp);
		return (0);
	}
	resplen = ns_get16(ans);
	if (resplen > anssiz) {
		Dprint(statp->options & RES_DEBUG,
		       (stdout, ";; response truncated\n")
		       );
		truncating = 1;
		len = anssiz;
	} else
		len = resplen;
	if (len < HFIXEDSZ) {
		/*
		 * Undersized message.
		 */
		Dprint(statp->options & RES_DEBUG,
		       (stdout, ";; undersized: %d\n", len));
		*terrno = EMSGSIZE;
		res_nclose(statp);
		return (0);
	}
	cp = ans;
	while (len != 0 &&
	    (n = _read(statp->_vcsock, (char *)cp, (int)len)) > 0) {
		cp += n;
		len -= n;
	}
	if (n <= 0) {
		*terrno = errno;
		Perror(statp, stderr, "read(vc)", errno);
		res_nclose(statp);
		return (0);
	}
	if (truncating) {
		/*
		 * Flush rest of answer so connection stays in synch.
		 */
		anhp->tc = 1;
		len = resplen - anssiz;
		while (len != 0) {
			char junk[PACKETSZ];

			n = _read(statp->_vcsock, junk,
			    (len > sizeof junk) ? sizeof junk : len);
			if (n > 0)
				len -= n;
			else
				break;
		}
	}
	/*
	 * If the calling applicating has bailed out of
	 * a previous call and failed to arrange to have
	 * the circuit closed or the server has got
	 * itself confused, then drop the packet and
	 * wait for the correct one.
	 */
	if (hp->id != anhp->id) {
		DprintQ((statp->options & RES_DEBUG) ||
			(statp->pfcode & RES_PRF_REPLY),
			(stdout, ";; old answer (unexpected):\n"),
			ans, (resplen > anssiz) ? anssiz: resplen);
		goto read_len;
	}

	/*
	 * All is well, or the error is fatal.  Signal that the
	 * next nameserver ought not be tried.
	 */
	return (resplen);
}