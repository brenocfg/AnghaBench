#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_10__ {int fd; scalar_t__ needs_removal; } ;
struct TYPE_9__ {int count; } ;
typedef  TYPE_1__ ChildMonitor ;
typedef  int /*<<< orphan*/  Child ;

/* Variables and functions */
 TYPE_2__ EMPTY_CHILD ; 
 size_t EXTRA_FDS ; 
 TYPE_2__* children ; 
 int /*<<< orphan*/  cleanup_child (size_t) ; 
 TYPE_2__* fds ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,size_t) ; 
 TYPE_2__* remove_queue ; 
 size_t remove_queue_count ; 

__attribute__((used)) static inline void
remove_children(ChildMonitor *self) {
    if (self->count > 0) {
        size_t count = 0;
        for (ssize_t i = self->count - 1; i >= 0; i--) {
            if (children[i].needs_removal) {
                count++;
                cleanup_child(i);
                remove_queue[remove_queue_count] = children[i];
                remove_queue_count++;
                children[i] = EMPTY_CHILD;
                fds[EXTRA_FDS + i].fd = -1;
                size_t num_to_right = self->count - 1 - i;
                if (num_to_right > 0) {
                    memmove(children + i, children + i + 1, num_to_right * sizeof(Child));
                    memmove(fds + EXTRA_FDS + i, fds + EXTRA_FDS + i + 1, num_to_right * sizeof(struct pollfd));
                }
            }
        }
        self->count -= count;
    }
}