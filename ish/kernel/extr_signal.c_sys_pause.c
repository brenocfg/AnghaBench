#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int_t ;
struct TYPE_4__ {TYPE_1__* sighand; int /*<<< orphan*/  pause; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ _EINTR ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int_t sys_pause() {
    lock(&current->sighand->lock);
    while (wait_for(&current->pause, &current->sighand->lock, NULL) != _EINTR)
        continue;
    unlock(&current->sighand->lock);
    return _EINTR;
}