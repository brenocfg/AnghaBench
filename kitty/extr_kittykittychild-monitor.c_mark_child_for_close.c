#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ id_type ;
struct TYPE_5__ {scalar_t__ id; int needs_removal; } ;
struct TYPE_4__ {size_t count; } ;
typedef  TYPE_1__ ChildMonitor ;

/* Variables and functions */
 TYPE_3__* children ; 
 int /*<<< orphan*/  children_mutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  unlock ; 
 int /*<<< orphan*/  wakeup_io_loop (int) ; 

__attribute__((used)) static inline void
mark_child_for_close(ChildMonitor *self, id_type window_id) {
    children_mutex(lock);
    for (size_t i = 0; i < self->count; i++) {
        if (children[i].id == window_id) {
            children[i].needs_removal = true;
            break;
        }
    }
    children_mutex(unlock);
    wakeup_io_loop(false);
}