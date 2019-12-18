#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  fd_mask ;
struct TYPE_6__ {int c_fd; struct timeval c_tv; } ;
typedef  TYPE_1__ con ;
struct TYPE_7__ {int /*<<< orphan*/  c_name; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_link ; 
 int /*<<< orphan*/  confree (int) ; 
 int /*<<< orphan*/  conread (int) ; 
 int /*<<< orphan*/  conrecycle (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* fdcon ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int maxfd ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monotime_tv (struct timeval*) ; 
 int /*<<< orphan*/  read_wait ; 
 int read_wait_nfdset ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  timerclear (struct timeval*) ; 
 int /*<<< orphan*/  tq ; 
 int /*<<< orphan*/ * xcalloc (int,int) ; 

__attribute__((used)) static void
conloop(void)
{
	struct timeval seltime, now;
	fd_set *r, *e;
	con *c;
	int i;

	monotime_tv(&now);
	c = TAILQ_FIRST(&tq);

	if (c && (c->c_tv.tv_sec > now.tv_sec ||
	    (c->c_tv.tv_sec == now.tv_sec && c->c_tv.tv_usec > now.tv_usec))) {
		seltime = c->c_tv;
		seltime.tv_sec -= now.tv_sec;
		seltime.tv_usec -= now.tv_usec;
		if (seltime.tv_usec < 0) {
			seltime.tv_usec += 1000000;
			seltime.tv_sec--;
		}
	} else
		timerclear(&seltime);

	r = xcalloc(read_wait_nfdset, sizeof(fd_mask));
	e = xcalloc(read_wait_nfdset, sizeof(fd_mask));
	memcpy(r, read_wait, read_wait_nfdset * sizeof(fd_mask));
	memcpy(e, read_wait, read_wait_nfdset * sizeof(fd_mask));

	while (select(maxfd, r, NULL, e, &seltime) == -1 &&
	    (errno == EAGAIN || errno == EINTR || errno == EWOULDBLOCK))
		;

	for (i = 0; i < maxfd; i++) {
		if (FD_ISSET(i, e)) {
			error("%s: exception!", fdcon[i].c_name);
			confree(i);
		} else if (FD_ISSET(i, r))
			conread(i);
	}
	free(r);
	free(e);

	c = TAILQ_FIRST(&tq);
	while (c && (c->c_tv.tv_sec < now.tv_sec ||
	    (c->c_tv.tv_sec == now.tv_sec && c->c_tv.tv_usec < now.tv_usec))) {
		int s = c->c_fd;

		c = TAILQ_NEXT(c, c_link);
		conrecycle(s);
	}
}