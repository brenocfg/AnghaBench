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
struct timeval {int tv_sec; int tv_usec; } ;
struct params {int bint; int rx; int tap; int /*<<< orphan*/  plast; scalar_t__ packet_try; int /*<<< orphan*/  blast; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int elapsed (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_tap (struct params*) ; 
 int /*<<< orphan*/  read_wifi (struct params*) ; 
 scalar_t__ retransmit (struct params*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send_beacon (struct params*) ; 

void next_event(struct params *p)
{
	struct timeval to, now;
	int el;
	int max;
	fd_set fds;
	int rtr = 3*1000;

	/* figure out select timeout */
	if (gettimeofday(&now, NULL) == -1)
		err(1, "gettimeofday()");

	/* check beacon timeout */
	el = elapsed(&p->blast, &now);
	if (el >= p->bint) {
		send_beacon(p);
		el = 0;
	}
	el = p->bint - el;
	to.tv_sec = el/1000/1000;
	to.tv_usec = el - to.tv_sec*1000*1000;

	/* check tx timeout */
	if (p->packet_try) {
		el = elapsed(&p->plast, &now);
		if (el >= rtr) {
			/* check if we gotta retransmit more */
			if (retransmit(p)) {
				el = 0;
			}
			else
				el = -1;
		}

		/* gotta retransmit in future */
		if (el != -1) {
			el = rtr - el;
			if ((to.tv_sec*1000*1000 + to.tv_usec) > el) {
				to.tv_sec = el/1000/1000;
				to.tv_usec = el - to.tv_sec*1000*1000;
			}
		}
	}

	/* select */
	FD_ZERO(&fds);
	FD_SET(p->rx, &fds);
	FD_SET(p->tap, &fds);
	max = p->rx > p->tap ? p->rx : p->tap;
	if (select(max+1, &fds, NULL, NULL, &to) == -1)
		err(1, "select()");

	if (FD_ISSET(p->tap, &fds))
		read_tap(p);
	if (FD_ISSET(p->rx, &fds))
		read_wifi(p);
}