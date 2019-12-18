#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct params {scalar_t__ state; scalar_t__ rx; TYPE_1__* q; int /*<<< orphan*/  last; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {scalar_t__ live; } ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ S_START ; 
 scalar_t__ S_WAIT_RELAY ; 
 int elapsed (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_wifi (struct params*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send_queue (struct params*) ; 

void own(struct params *p)
{
	struct timeval tv;
	struct timeval *to = NULL;
	fd_set fds;
	int tout = 10*1000;

	if (p->state == S_WAIT_RELAY) {
		int el;

		/* check timeout */
		if (gettimeofday(&tv, NULL) == -1)
			err(1, "gettimeofday()");
	
		el = elapsed(&p->last, &tv);

		/* timeout */
		if (el >= tout) {
			if (p->q && p->q->live) {
				send_queue(p);
				el = 0;
			} else {
				p->state = S_START;
				return;
			}
		}
		el = tout - el;
		tv.tv_sec = el/1000/1000;
		tv.tv_usec = el - tv.tv_sec*1000*1000;
		to = &tv;
	}

	FD_ZERO(&fds);
	FD_SET(p->rx, &fds);

	if (select(p->rx+1, &fds, NULL, NULL, to) == -1)
		err(1, "select()");

	if (FD_ISSET(p->rx, &fds))
		read_wifi(p);
}