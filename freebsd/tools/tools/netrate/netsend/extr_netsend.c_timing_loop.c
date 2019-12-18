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
typedef  long uint64_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int u_int ;
struct timespec {long tv_nsec; int tv_sec; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin_port; } ;
struct _a {long duration; int port; int port_max; int packet_len; TYPE_1__ sin; int /*<<< orphan*/  packet; int /*<<< orphan*/  s; int /*<<< orphan*/  sin6; scalar_t__ ipv6; struct timespec interval; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  be32enc (int /*<<< orphan*/ ,scalar_t__) ; 
 int clock_getres (int /*<<< orphan*/ ,struct timespec*) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int sendto (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  timespec_add (struct timespec*,struct timespec*) ; 
 scalar_t__ timespec_ge (struct timespec*,struct timespec*) ; 
 int wait_time (struct timespec,struct timespec*,long long*) ; 

__attribute__((used)) static int
timing_loop(struct _a *a)
{
	struct timespec nexttime, starttime, tmptime;
	long long waited;
	u_int32_t counter;
	long finishtime;
	long send_errors, send_calls;
	/* do not call gettimeofday more than every 20us */
	long minres_ns = 200000;
	int ic, gettimeofday_cycles;
	int cur_port;
	uint64_t n, ns;

	if (clock_getres(CLOCK_REALTIME, &tmptime) == -1) {
		perror("clock_getres");
		return (-1);
	}

	ns = a->interval.tv_nsec;
	if (timespec_ge(&tmptime, &a->interval))
		fprintf(stderr,
		    "warning: interval (%jd.%09ld) less than resolution (%jd.%09ld)\n",
		    (intmax_t)a->interval.tv_sec, a->interval.tv_nsec,
		    (intmax_t)tmptime.tv_sec, tmptime.tv_nsec);
		/* interval too short, limit the number of gettimeofday()
		 * calls, but also make sure there is at least one every
		 * some 100 packets.
		 */
	if ((long)ns < minres_ns/100)
		gettimeofday_cycles = 100;
	else
		gettimeofday_cycles = minres_ns/ns;
	fprintf(stderr,
	    "calling time every %d cycles\n", gettimeofday_cycles);

	if (clock_gettime(CLOCK_REALTIME, &starttime) == -1) {
		perror("clock_gettime");
		return (-1);
	}
	tmptime.tv_sec = 2;
	tmptime.tv_nsec = 0;
	timespec_add(&starttime, &tmptime);
	starttime.tv_nsec = 0;
	if (wait_time(starttime, NULL, NULL) == -1)
		return (-1);
	nexttime = starttime;
	finishtime = starttime.tv_sec + a->duration;

	send_errors = send_calls = 0;
	counter = 0;
	waited = 0;
	ic = gettimeofday_cycles;
	cur_port = a->port;
	if (a->port == a->port_max) {
		if (a->ipv6) {
			if (connect(a->s, (struct sockaddr *)&a->sin6, sizeof(a->sin6))) {
				perror("connect (ipv6)");
				return (-1);
			}
		} else {
			if (connect(a->s, (struct sockaddr *)&a->sin, sizeof(a->sin))) {
				perror("connect (ipv4)");
				return (-1);
			}
		}
	}
	while (1) {
		int ret;

		timespec_add(&nexttime, &a->interval);
		if (--ic <= 0) {
			ic = gettimeofday_cycles;
			if (wait_time(nexttime, &tmptime, &waited) == -1)
				return (-1);
		}
		/*
		 * We maintain and, if there's room, send a counter.  Note
		 * that even if the error is purely local, we still increment
		 * the counter, so missing sequence numbers on the receive
		 * side should not be assumed to be packets lost in transit.
		 * For example, if the UDP socket gets back an ICMP from a
		 * previous send, the error will turn up the current send
		 * operation, causing the current sequence number also to be
		 * skipped.
		 * The counter is incremented only on the initial port number,
		 * so all destinations will see the same set of packets.
		 */
		if (cur_port == a->port && a->packet_len >= 4) {
			be32enc(a->packet, counter);
			counter++;
		}
		if (a->port == a->port_max) { /* socket already bound */
			ret = send(a->s, a->packet, a->packet_len, 0);
		} else {
			a->sin.sin_port = htons(cur_port++);
			if (cur_port > a->port_max)
				cur_port = a->port;
			if (a->ipv6) {
			ret = sendto(a->s, a->packet, a->packet_len, 0,
			    (struct sockaddr *)&a->sin6, sizeof(a->sin6));
			} else {
			ret = sendto(a->s, a->packet, a->packet_len, 0,
				(struct sockaddr *)&a->sin, sizeof(a->sin));
			}
		}
		if (ret < 0)
			send_errors++;
		send_calls++;
		if (a->duration != 0 && tmptime.tv_sec >= finishtime)
			goto done;
	}

done:
	if (clock_gettime(CLOCK_REALTIME, &tmptime) == -1) {
		perror("clock_gettime");
		return (-1);
	}

	printf("\n");
	printf("start:             %jd.%09ld\n", (intmax_t)starttime.tv_sec,
	    starttime.tv_nsec);
	printf("finish:            %jd.%09ld\n", (intmax_t)tmptime.tv_sec,
	    tmptime.tv_nsec);
	printf("send calls:        %ld\n", send_calls);
	printf("send errors:       %ld\n", send_errors);
	printf("approx send rate:  %ld pps\n", (send_calls - send_errors) /
	    a->duration);
	n = send_calls - send_errors;
	if (n > 0) {
		ns = (tmptime.tv_sec - starttime.tv_sec) * 1000000000UL +
			(tmptime.tv_nsec - starttime.tv_nsec);
		n = ns / n;
	}
	printf("time/packet:       %u ns\n", (u_int)n);
	printf("approx error rate: %ld\n", (send_errors / send_calls));
	printf("waited:            %lld\n", waited);
	printf("approx waits/sec:  %lld\n", (long long)(waited / a->duration));
	printf("approx wait rate:  %lld\n", (long long)(waited / send_calls));

	return (0);
}