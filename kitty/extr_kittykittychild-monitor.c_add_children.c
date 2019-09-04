#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_7__ {size_t count; } ;
typedef  TYPE_1__ ChildMonitor ;

/* Variables and functions */
 TYPE_3__ EMPTY_CHILD ; 
 size_t EXTRA_FDS ; 
 size_t MAX_CHILDREN ; 
 int /*<<< orphan*/  POLLIN ; 
 TYPE_3__* add_queue ; 
 size_t add_queue_count ; 
 TYPE_3__* children ; 
 TYPE_2__* fds ; 

__attribute__((used)) static inline void
add_children(ChildMonitor *self) {
    for (; add_queue_count > 0 && self->count < MAX_CHILDREN;) {
        add_queue_count--;
        children[self->count] = add_queue[add_queue_count];
        add_queue[add_queue_count] = EMPTY_CHILD;
        fds[EXTRA_FDS + self->count].fd = children[self->count].fd;
        fds[EXTRA_FDS + self->count].events = POLLIN;
        self->count++;
    }
}