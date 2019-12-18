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
typedef  int uint64_t ;
typedef  scalar_t__ u_int64_t ;
typedef  int u_int ;
typedef  scalar_t__ time_t ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_2__ {scalar_t__ client_alive_interval; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 scalar_t__ MINIMUM (scalar_t__,int) ; 
 scalar_t__ channel_not_very_much_buffered_data () ; 
 int /*<<< orphan*/  channel_prepare_select (struct ssh*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int*,int*,scalar_t__*) ; 
 scalar_t__ child_terminated ; 
 int /*<<< orphan*/  client_alive_check (struct ssh*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ monotime () ; 
 int /*<<< orphan*/  notify_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_prepare (int /*<<< orphan*/ *) ; 
 TYPE_1__ options ; 
 scalar_t__ packet_have_data_to_write () ; 
 scalar_t__ packet_not_very_much_data_to_write () ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void
wait_until_can_do_something(struct ssh *ssh,
    int connection_in, int connection_out,
    fd_set **readsetp, fd_set **writesetp, int *maxfdp,
    u_int *nallocp, u_int64_t max_time_ms)
{
	struct timeval tv, *tvp;
	int ret;
	time_t minwait_secs = 0;
	int client_alive_scheduled = 0;
	static time_t last_client_time;

	/* Allocate and update select() masks for channel descriptors. */
	channel_prepare_select(ssh, readsetp, writesetp, maxfdp,
	    nallocp, &minwait_secs);

	/* XXX need proper deadline system for rekey/client alive */
	if (minwait_secs != 0)
		max_time_ms = MINIMUM(max_time_ms, (u_int)minwait_secs * 1000);

	/*
	 * if using client_alive, set the max timeout accordingly,
	 * and indicate that this particular timeout was for client
	 * alive by setting the client_alive_scheduled flag.
	 *
	 * this could be randomized somewhat to make traffic
	 * analysis more difficult, but we're not doing it yet.
	 */
	if (options.client_alive_interval) {
		uint64_t keepalive_ms =
		    (uint64_t)options.client_alive_interval * 1000;

		client_alive_scheduled = 1;
		if (max_time_ms == 0 || max_time_ms > keepalive_ms)
			max_time_ms = keepalive_ms;
	}

#if 0
	/* wrong: bad condition XXX */
	if (channel_not_very_much_buffered_data())
#endif
	FD_SET(connection_in, *readsetp);
	notify_prepare(*readsetp);

	/*
	 * If we have buffered packet data going to the client, mark that
	 * descriptor.
	 */
	if (packet_have_data_to_write())
		FD_SET(connection_out, *writesetp);

	/*
	 * If child has terminated and there is enough buffer space to read
	 * from it, then read as much as is available and exit.
	 */
	if (child_terminated && packet_not_very_much_data_to_write())
		if (max_time_ms == 0 || client_alive_scheduled)
			max_time_ms = 100;

	if (max_time_ms == 0)
		tvp = NULL;
	else {
		tv.tv_sec = max_time_ms / 1000;
		tv.tv_usec = 1000 * (max_time_ms % 1000);
		tvp = &tv;
	}

	/* Wait for something to happen, or the timeout to expire. */
	ret = select((*maxfdp)+1, *readsetp, *writesetp, NULL, tvp);

	if (ret == -1) {
		memset(*readsetp, 0, *nallocp);
		memset(*writesetp, 0, *nallocp);
		if (errno != EINTR)
			error("select: %.100s", strerror(errno));
	} else if (client_alive_scheduled) {
		time_t now = monotime();

		if (ret == 0) { /* timeout */
			client_alive_check(ssh);
		} else if (FD_ISSET(connection_in, *readsetp)) {
			last_client_time = now;
		} else if (last_client_time != 0 && last_client_time +
		    options.client_alive_interval <= now) {
			client_alive_check(ssh);
			last_client_time = now;
		}
	}

	notify_done(*readsetp);
}