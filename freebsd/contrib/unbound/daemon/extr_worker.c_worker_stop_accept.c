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
struct worker {scalar_t__ thread_num; TYPE_1__* daemon; int /*<<< orphan*/  front; } ;
struct TYPE_2__ {int /*<<< orphan*/  rc; } ;

/* Variables and functions */
 int /*<<< orphan*/  daemon_remote_stop_accept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_stop_accept (int /*<<< orphan*/ ) ; 

void worker_stop_accept(void* arg)
{
	struct worker* worker = (struct worker*)arg;
	listen_stop_accept(worker->front);
	if(worker->thread_num == 0)
		daemon_remote_stop_accept(worker->daemon->rc);
}