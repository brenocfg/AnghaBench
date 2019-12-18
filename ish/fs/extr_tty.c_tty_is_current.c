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
struct tty {int dummy; } ;
struct TYPE_4__ {TYPE_1__* group; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; struct tty* tty; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tty_is_current(struct tty *tty) {
    lock(&current->group->lock);
    bool is_current = current->group->tty == tty;
    unlock(&current->group->lock);
    return is_current;
}