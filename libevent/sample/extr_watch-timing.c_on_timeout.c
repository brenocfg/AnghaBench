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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  delays ; 
 int /*<<< orphan*/  durations ; 
 double histogram_query (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double) ; 

__attribute__((used)) static void
on_timeout(evutil_socket_t fd, short events, void *arg)
{
	printf("durations: [p50 = %fs, p95 = %fs], delays: [p50 = %fs, p95 = %fs]\n",
		histogram_query(durations, 0.5),
		histogram_query(durations, 0.95),
		histogram_query(delays, 0.5),
		histogram_query(delays, 0.95));
}