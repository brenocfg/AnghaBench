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
struct TYPE_2__ {scalar_t__ val; } ;
struct fd {int /*<<< orphan*/  lock; TYPE_1__ eventfd; } ;

/* Variables and functions */
 int POLL_READ ; 
 int POLL_WRITE ; 
 int UINT64_MAX ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eventfd_poll(struct fd *fd) {
    lock(&fd->lock);
    int types = 0;
    if (fd->eventfd.val > 0)
        types |= POLL_READ;
    if (fd->eventfd.val < UINT64_MAX - 1)
        types |= POLL_WRITE;
    unlock(&fd->lock);
    return types;
}