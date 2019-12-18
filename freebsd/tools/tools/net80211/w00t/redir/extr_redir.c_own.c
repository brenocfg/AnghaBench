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
struct params {scalar_t__ state; int data_try; int rx; int s; int /*<<< orphan*/  last; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ S_START ; 
 scalar_t__ S_WAIT_ACK ; 
 scalar_t__ S_WAIT_BUDDY ; 
 int elapsed (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_buddy (struct params*) ; 
 int /*<<< orphan*/  read_wifi (struct params*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send_packet (struct params*) ; 

void own(struct params *p)
{
	struct timeval tv;
	struct timeval *to = NULL;
	fd_set fds;
	int max;
	int tout_ack = 10*1000;
	int tout_buddy = 2*1000*1000;
	int tout = (p->state == S_WAIT_BUDDY) ? tout_buddy : tout_ack;

	if (p->state == S_WAIT_ACK || p->state == S_WAIT_BUDDY) {
		int el;

		/* check timeout */
		if (gettimeofday(&tv, NULL) == -1)
			err(1, "gettimeofday()");
	
		el = elapsed(&p->last, &tv);

		/* timeout */
		if (el >= tout) {
			if (p->data_try > 3) {
				p->state = S_START;
				return;
			} else {
				send_packet(p);
				el = 0;
			}
		}
		el = tout - el;
		tv.tv_sec = el/1000/1000;
		tv.tv_usec = el - tv.tv_sec*1000*1000;
		to = &tv;
	}

	FD_ZERO(&fds);
	FD_SET(p->rx, &fds);
	FD_SET(p->s, &fds);
	max = (p->rx > p->s) ? p->rx : p->s;

	if (select(max+1, &fds, NULL, NULL, to) == -1)
		err(1, "select()");

	if (FD_ISSET(p->rx, &fds))
		read_wifi(p);
	if (FD_ISSET(p->s, &fds))
		read_buddy(p);
}