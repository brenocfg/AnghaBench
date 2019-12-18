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
struct timeval {int dummy; } ;
struct request_info {int /*<<< orphan*/  started; scalar_t__ n_read; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 short BEV_EVENT_EOF ; 
 int EV_READ ; 
 int EV_WRITE ; 
 scalar_t__ N_REQUESTS ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timeradd (struct timeval*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_timersub (struct timeval*,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  free (struct request_info*) ; 
 scalar_t__ launch_request () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  total_n_bytes ; 
 int /*<<< orphan*/  total_n_errors ; 
 int total_n_handled ; 
 scalar_t__ total_n_launched ; 
 int /*<<< orphan*/  total_time ; 

__attribute__((used)) static void
errorcb(struct bufferevent *b, short what, void *arg)
{
	struct request_info *ri = arg;
	struct timeval now, diff;
	if (what & BEV_EVENT_EOF) {
		++total_n_handled;
		total_n_bytes += ri->n_read;
		evutil_gettimeofday(&now, NULL);
		evutil_timersub(&now, &ri->started, &diff);
		evutil_timeradd(&diff, &total_time, &total_time);

		if (total_n_handled && (total_n_handled%1000)==0)
			printf("%d requests done\n",total_n_handled);

		if (total_n_launched < N_REQUESTS) {
			if (launch_request() < 0)
				perror("Can't launch");
		}
	} else {
		++total_n_errors;
		perror("Unexpected error");
	}

	bufferevent_setcb(b, NULL, NULL, NULL, NULL);
	free(ri);
	bufferevent_disable(b, EV_READ|EV_WRITE);
	bufferevent_free(b);
}