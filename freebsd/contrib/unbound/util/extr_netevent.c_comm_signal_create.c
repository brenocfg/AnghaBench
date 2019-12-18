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
struct comm_signal {void (* callback ) (int,void*) ;int /*<<< orphan*/ * ev_signal; void* cb_arg; struct comm_base* base; } ;
struct comm_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 

struct comm_signal* 
comm_signal_create(struct comm_base* base,
        void (*callback)(int, void*), void* cb_arg)
{
	struct comm_signal* com = (struct comm_signal*)malloc(
		sizeof(struct comm_signal));
	if(!com) {
		log_err("malloc failed");
		return NULL;
	}
	com->base = base;
	com->callback = callback;
	com->cb_arg = cb_arg;
	com->ev_signal = NULL;
	return com;
}