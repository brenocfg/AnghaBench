#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct sockaddr_l2cap {int /*<<< orphan*/  l2cap_bdaddr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  ra ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  mtu ;
typedef  int /*<<< orphan*/  mru ;
typedef  int /*<<< orphan*/  la ;
struct TYPE_6__ {int mru; int mtu; int /*<<< orphan*/  state; int /*<<< orphan*/  laddr; int /*<<< orphan*/  raddr; int /*<<< orphan*/  recv; int /*<<< orphan*/  send; } ;
typedef  TYPE_1__ channel_t ;

/* Variables and functions */
 int BNEP_MTU_MIN ; 
 int /*<<< orphan*/  CHANNEL_CLOSED ; 
 int /*<<< orphan*/  CHANNEL_WAIT_CONNECT_REQ ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  SOL_L2CAP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_L2CAP_IMTU ; 
 int /*<<< orphan*/  SO_L2CAP_OMTU ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  SO_SNDLOWAT ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  b2eaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnep_recv ; 
 int /*<<< orphan*/  bnep_send ; 
 int bt_ntoa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* channel_alloc () ; 
 int /*<<< orphan*/  channel_free (TYPE_1__*) ; 
 int /*<<< orphan*/  channel_open (TYPE_1__*,int) ; 
 int /*<<< orphan*/  channel_timeout (TYPE_1__*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int getsockname (int,struct sockaddr*,int*) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_info (char*,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
server_read(int s, short ev, void *arg)
{
	struct sockaddr_l2cap ra, la;
	channel_t *chan;
	socklen_t len;
	int fd, n;
	uint16_t mru, mtu;

	len = sizeof(ra);
	fd = accept(s, (struct sockaddr *)&ra, &len);
	if (fd == -1)
		return;

	n = 1;
	if (ioctl(fd, FIONBIO, &n) == -1) {
		log_err("Could not set NonBlocking IO: %m");
		close(fd);
		return;
	}

	len = sizeof(mru);
	if (getsockopt(fd, SOL_L2CAP, SO_L2CAP_IMTU, &mru, &len) == -1) {
		log_err("Could not get L2CAP IMTU: %m");
		close(fd);
		return;
	}
	if(mru < BNEP_MTU_MIN) {
		log_err("L2CAP IMTU too small (%d)", mru);
		close(fd);
		return;
	}

	len = sizeof(n);
	if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &n, &len) == -1) {
		log_err("Could not read SO_RCVBUF");
		close(fd);
		return;
	}
	if (n < (mru * 10)) {
		n = mru * 10;
		if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n)) == -1)
			log_info("Could not increase SO_RCVBUF (from %d)", n);
	}

	len = sizeof(mtu);
	if (getsockopt(fd, SOL_L2CAP, SO_L2CAP_OMTU, &mtu, &len) == -1) {
		log_err("Could not get L2CAP OMTU: %m");
		close(fd);
		return;
	}
	if (mtu < BNEP_MTU_MIN) {
		log_err("L2CAP OMTU too small (%d)", mtu);
		close(fd);
		return;
	}

	len = sizeof(n);
	if (getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &n, &len) == -1) {
		log_err("Could not get socket send buffer size: %m");
		close(fd);
		return;
	}

	if (n < (mtu * 2)) {
		n = mtu * 2;
		if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &n, sizeof(n)) == -1) {
			log_err("Could not set socket send buffer size (%d): %m", n);
			close(fd);
			return;
		}
	}

	n = mtu;
	if (setsockopt(fd, SOL_SOCKET, SO_SNDLOWAT, &n, sizeof(n)) == -1) {
		log_err("Could not set socket low water mark (%d): %m", n);
		close(fd);
		return;
	}

	len = sizeof(la);
	if (getsockname(fd, (struct sockaddr *)&la, &len) == -1) {
		log_err("Could not get socket address: %m");
		close(fd);
		return;
	}

	log_info("Accepted connection from %s", bt_ntoa(&ra.l2cap_bdaddr, NULL));

	chan = channel_alloc();
	if (chan == NULL) {
		close(fd);
		return;
	}

	chan->send = bnep_send;
	chan->recv = bnep_recv;
	chan->mru = mru;
	chan->mtu = mtu;
	b2eaddr(chan->raddr, &ra.l2cap_bdaddr);
	b2eaddr(chan->laddr, &la.l2cap_bdaddr);
	chan->state = CHANNEL_WAIT_CONNECT_REQ;
	channel_timeout(chan, 10);
	if (!channel_open(chan, fd)) {
		chan->state = CHANNEL_CLOSED;
		channel_free(chan);
		close(fd);
		return;
	}
}