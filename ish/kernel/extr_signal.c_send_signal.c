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
struct task {TYPE_1__* group; struct sighand* sighand; scalar_t__ zombie; } ;
struct siginfo_ {int dummy; } ;
struct sighand {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int stopped; int /*<<< orphan*/  lock; int /*<<< orphan*/  stopped_cond; } ;

/* Variables and functions */
 int SIGCONT_ ; 
 int SIGKILL_ ; 
 scalar_t__ SIGNAL_IGNORE ; 
 int /*<<< orphan*/  deliver_signal_unlocked (struct task*,int,struct siginfo_) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_action (struct sighand*,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void send_signal(struct task *task, int sig, struct siginfo_ info) {
    // signal zero is for testing whether a process exists
    if (sig == 0)
        return;
    if (task->zombie)
        return;

    struct sighand *sighand = task->sighand;
    lock(&sighand->lock);
    if (signal_action(sighand, sig) != SIGNAL_IGNORE) {
        deliver_signal_unlocked(task, sig, info);
    }
    unlock(&sighand->lock);

    if (sig == SIGCONT_ || sig == SIGKILL_) {
        lock(&task->group->lock);
        task->group->stopped = false;
        notify(&task->group->stopped_cond);
        unlock(&task->group->lock);
    }
}