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
struct TYPE_2__ {int /*<<< orphan*/  expirations; } ;
struct fd {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; TYPE_1__ timerfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wakeup (struct fd*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timerfd_callback(struct fd *fd) {
    lock(&fd->lock);
    fd->timerfd.expirations++;
    notify(&fd->cond);
    unlock(&fd->lock);
    poll_wakeup(fd);
}