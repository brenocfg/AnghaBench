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
struct comm_base {void (* stop_accept ) (void*) ;void (* start_accept ) (void*) ;void* cb_arg; } ;

/* Variables and functions */

void comm_base_set_slow_accept_handlers(struct comm_base* b,
	void (*stop_acc)(void*), void (*start_acc)(void*), void* arg)
{
	b->stop_accept = stop_acc;
	b->start_accept = start_acc;
	b->cb_arg = arg;
}