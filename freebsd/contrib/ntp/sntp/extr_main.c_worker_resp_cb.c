#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ evutil_socket_t ;
struct TYPE_3__ {scalar_t__ resp_read_pipe; } ;
typedef  TYPE_1__ blocking_child ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INSIST (int) ; 
 short EV_READ ; 
 int /*<<< orphan*/  process_blocking_resp (TYPE_1__*) ; 

void
worker_resp_cb(
	evutil_socket_t	fd,
	short		what,
	void *		ctx	/* blocking_child * */
	)
{
	blocking_child *	c;

	DEBUG_INSIST(EV_READ & what);
	c = ctx;
	DEBUG_INSIST(fd == c->resp_read_pipe);
	process_blocking_resp(c);
}