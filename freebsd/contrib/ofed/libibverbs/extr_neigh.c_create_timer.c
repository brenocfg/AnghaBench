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
struct timespec {int tv_sec; int tv_nsec; } ;
struct itimerspec {struct timespec it_interval; struct timespec it_value; } ;
struct get_neigh_handler {int timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int NUM_OF_TRIES ; 
 int TFD_CLOEXEC ; 
 int TFD_NONBLOCK ; 
 int /*<<< orphan*/  bzero (struct timespec*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int timerfd_create (int /*<<< orphan*/ ,int) ; 
 scalar_t__ timerfd_settime (int,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_timer(struct get_neigh_handler *neigh_handler)
{
	int user_timeout = neigh_handler->timeout/NUM_OF_TRIES;
	struct timespec timeout = {
		.tv_sec = user_timeout / 1000,
		.tv_nsec = (user_timeout % 1000) * 1000000
	};
	struct itimerspec timer_time = {.it_value = timeout};
	int timer_fd;

	timer_fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
	if (timer_fd == -1)
		return timer_fd;

	if (neigh_handler->timeout) {
		if (NUM_OF_TRIES <= 1)
			bzero(&timer_time.it_interval,
			      sizeof(timer_time.it_interval));
		else
			timer_time.it_interval = timeout;
		if (timerfd_settime(timer_fd, 0, &timer_time, NULL)) {
			close(timer_fd);
			return -1;
		}
	}

	return timer_fd;
}