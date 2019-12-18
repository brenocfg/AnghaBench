#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_5__ {TYPE_1__* task; } ;
struct TYPE_4__ {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 TYPE_2__* current_thread () ; 
 int /*<<< orphan*/ * kernel_map ; 

bool
db_map_current(vm_map_t map)
{
#if 0
	thread_t	thread;

	return ((map == NULL) ||
		(map == kernel_map) ||
		(((thread = current_thread()) != NULL) &&
		 (map == thread->task->map)));
#else
	return (true);
#endif
}