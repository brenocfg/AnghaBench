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
struct tty {int /*<<< orphan*/  fg_group; int /*<<< orphan*/  session; int /*<<< orphan*/  refcount; } ;
struct tgroup {int /*<<< orphan*/  lock; int /*<<< orphan*/  pgid; int /*<<< orphan*/  sid; struct tty* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tty_set_controlling(struct tgroup *group, struct tty *tty) {
    lock(&group->lock);
    if (group->tty == NULL) {
        tty->refcount++;
        group->tty = tty;
        tty->session = group->sid;
        tty->fg_group = group->pgid;
    }
    unlock(&group->lock);
}