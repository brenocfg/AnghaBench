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
struct evdev_client {int ec_clock_id; } ;

/* Variables and functions */
#define  EV_CLOCK_BOOTTIME 130 
#define  EV_CLOCK_MONOTONIC 129 
#define  EV_CLOCK_REALTIME 128 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 

__attribute__((used)) static void
evdev_client_gettime(struct evdev_client *client, struct timeval *tv)
{

	switch (client->ec_clock_id) {
	case EV_CLOCK_BOOTTIME:
		/*
		 * XXX: FreeBSD does not support true POSIX monotonic clock.
		 *      So aliase EV_CLOCK_BOOTTIME to EV_CLOCK_MONOTONIC.
		 */
	case EV_CLOCK_MONOTONIC:
		microuptime(tv);
		break;

	case EV_CLOCK_REALTIME:
	default:
		microtime(tv);
		break;
	}
}