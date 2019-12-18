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
typedef  int /*<<< orphan*/  thetime ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct servent {int /*<<< orphan*/  s_port; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINTR ; 
 scalar_t__ EIO ; 
 scalar_t__ ETIMEDOUT ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 scalar_t__ TOFFSET ; 
 scalar_t__ _connect (int,struct sockaddr*,int) ; 
 int _read (int,char*,int) ; 
 int _recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  _rpc_dtablesize () ; 
 int _select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int _sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int _socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_close (int) ; 
 scalar_t__ errno ; 
 struct servent* getservbyname (char*,char*) ; 
 unsigned long ntohl (unsigned long) ; 

int
rtime(struct sockaddr_in *addrp, struct timeval *timep,
    struct timeval *timeout)
{
	int s;
	fd_set readfds;
	int res;
	unsigned long thetime;
	struct sockaddr_in from;
	socklen_t fromlen;
	int type;
	struct servent *serv;

	if (timeout == NULL) {
		type = SOCK_STREAM;
	} else {
		type = SOCK_DGRAM;
	}
	s = _socket(AF_INET, type, 0);
	if (s < 0) {
		return(-1);
	}
	addrp->sin_family = AF_INET;

	/* TCP and UDP port are the same in this case */
	if ((serv = getservbyname("time", "tcp")) == NULL) {
		return(-1);
	}

	addrp->sin_port = serv->s_port;

	if (type == SOCK_DGRAM) {
		res = _sendto(s, (char *)&thetime, sizeof(thetime), 0,
			     (struct sockaddr *)addrp, sizeof(*addrp));
		if (res < 0) {
			do_close(s);
			return(-1);
		}
		do {
			FD_ZERO(&readfds);
			FD_SET(s, &readfds);
			res = _select(_rpc_dtablesize(), &readfds,
				     (fd_set *)NULL, (fd_set *)NULL, timeout);
		} while (res < 0 && errno == EINTR);
		if (res <= 0) {
			if (res == 0) {
				errno = ETIMEDOUT;
			}
			do_close(s);
			return(-1);
		}
		fromlen = sizeof(from);
		res = _recvfrom(s, (char *)&thetime, sizeof(thetime), 0,
			       (struct sockaddr *)&from, &fromlen);
		do_close(s);
		if (res < 0) {
			return(-1);
		}
	} else {
		if (_connect(s, (struct sockaddr *)addrp, sizeof(*addrp)) < 0) {
			do_close(s);
			return(-1);
		}
		res = _read(s, (char *)&thetime, sizeof(thetime));
		do_close(s);
		if (res < 0) {
			return(-1);
		}
	}
	if (res != sizeof(thetime)) {
		errno = EIO;
		return(-1);
	}
	thetime = ntohl(thetime);
	timep->tv_sec = thetime - TOFFSET;
	timep->tv_usec = 0;
	return(0);
}