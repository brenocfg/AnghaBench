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
struct poll {int* notify_pipe; int /*<<< orphan*/  lock; int /*<<< orphan*/  poll_fds; scalar_t__ waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_init (int /*<<< orphan*/ *) ; 
 struct poll* malloc (int) ; 

struct poll *poll_create() {
    struct poll *poll = malloc(sizeof(struct poll));
    if (poll == NULL)
        return NULL;
    poll->waiters = 0;
    poll->notify_pipe[0] = -1;
    poll->notify_pipe[1] = -1;
    list_init(&poll->poll_fds);
    lock_init(&poll->lock);
    return poll;
}