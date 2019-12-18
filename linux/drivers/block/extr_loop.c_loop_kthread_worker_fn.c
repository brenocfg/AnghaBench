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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int PF_LESS_THROTTLE ; 
 int PF_MEMALLOC_NOIO ; 
 TYPE_1__* current ; 
 int kthread_worker_fn (void*) ; 

__attribute__((used)) static int loop_kthread_worker_fn(void *worker_ptr)
{
	current->flags |= PF_LESS_THROTTLE | PF_MEMALLOC_NOIO;
	return kthread_worker_fn(worker_ptr);
}