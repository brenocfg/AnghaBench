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
typedef  int /*<<< orphan*/  sigset_t_ ;
struct TYPE_4__ {TYPE_1__* sighand; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigmask_set_temp_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void sigmask_set_temp(sigset_t_ mask) {
    lock(&current->sighand->lock);
    sigmask_set_temp_unlocked(mask);
    unlock(&current->sighand->lock);
}