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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct kevent {int /*<<< orphan*/  data; int /*<<< orphan*/  ident; } ;
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct cfjail {int /*<<< orphan*/  pstatus; int /*<<< orphan*/  flags; TYPE_1__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  JF_TIMEOUT ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct cfjail* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  clear_procs (struct cfjail*) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errno ; 
 struct cfjail* find_proc (int /*<<< orphan*/ ) ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,struct timespec*) ; 
 int /*<<< orphan*/  kq ; 
 int /*<<< orphan*/  sleeping ; 
 int /*<<< orphan*/  waitpid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct cfjail *
next_proc(int nonblock)
{
	struct kevent ke;
	struct timespec ts;
	struct timespec *tsp;
	struct cfjail *j;

	if (!TAILQ_EMPTY(&sleeping)) {
	again:
		tsp = NULL;
		if ((j = TAILQ_FIRST(&sleeping)) && j->timeout.tv_sec) {
			clock_gettime(CLOCK_REALTIME, &ts);
			ts.tv_sec = j->timeout.tv_sec - ts.tv_sec;
			ts.tv_nsec = j->timeout.tv_nsec - ts.tv_nsec;
			if (ts.tv_nsec < 0) {
				ts.tv_sec--;
				ts.tv_nsec += 1000000000;
			}
			if (ts.tv_sec < 0 ||
			    (ts.tv_sec == 0 && ts.tv_nsec == 0)) {
				j->flags |= JF_TIMEOUT;
				clear_procs(j);
				return j;
			}
			tsp = &ts;
		}
		if (nonblock) {
			ts.tv_sec = 0;
			ts.tv_nsec = 0;
			tsp = &ts;
		}
		switch (kevent(kq, NULL, 0, &ke, 1, tsp)) {
		case -1:
			if (errno != EINTR)
				err(1, "kevent");
			goto again;
		case 0:
			if (!nonblock) {
				j = TAILQ_FIRST(&sleeping);
				j->flags |= JF_TIMEOUT;
				clear_procs(j);
				return j;
			}
			break;
		case 1:
			(void)waitpid(ke.ident, NULL, WNOHANG);
			if ((j = find_proc(ke.ident))) {
				j->pstatus = ke.data;
				return j;
			}
			goto again;
		}
	}
	return NULL;
}