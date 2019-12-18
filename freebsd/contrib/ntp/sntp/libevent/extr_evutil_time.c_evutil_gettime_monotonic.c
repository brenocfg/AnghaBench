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
struct evutil_monotonic_timer {int dummy; } ;

/* Variables and functions */
 int evutil_gettime_monotonic_ (struct evutil_monotonic_timer*,struct timeval*) ; 

int
evutil_gettime_monotonic(struct evutil_monotonic_timer *timer,
                         struct timeval *tp)
{
  return evutil_gettime_monotonic_(timer, tp);
}