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
typedef  void* evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_REQUIRE (short) ; 
 short EV_TIMEOUT ; 
 int /*<<< orphan*/  UNUSED_ARG (void*) ; 
 int /*<<< orphan*/  worker_idle_timer_fired () ; 

void
worker_timeout(
	evutil_socket_t	fd,
	short		what,
	void *		ctx
	)
{
	UNUSED_ARG(fd);
	UNUSED_ARG(ctx);

	DEBUG_REQUIRE(EV_TIMEOUT & what);
	worker_idle_timer_fired();
}