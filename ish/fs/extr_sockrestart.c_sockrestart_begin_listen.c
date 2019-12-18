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
struct TYPE_2__ {int /*<<< orphan*/  listen; } ;
struct fd {TYPE_1__ sockrestart; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listen_fds ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_fdops ; 
 int /*<<< orphan*/  sockrestart_lock ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void sockrestart_begin_listen(struct fd *sock) {
    if (sock->ops != &socket_fdops)
        return;
    lock(&sockrestart_lock);
    list_add(&listen_fds, &sock->sockrestart.listen);
    unlock(&sockrestart_lock);
}