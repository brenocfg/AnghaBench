#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  m; } ;
struct task {int pending; int blocked; int waiting; TYPE_1__* sighand; TYPE_2__ waiting_cond_lock; TYPE_2__* waiting_lock; int /*<<< orphan*/ * waiting_cond; int /*<<< orphan*/  thread; int /*<<< orphan*/  queue; } ;
struct siginfo_ {int sig; } ;
struct sigqueue {int /*<<< orphan*/  queue; struct siginfo_ info; } ;
struct TYPE_4__ {TYPE_2__ lock; } ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 struct task* current ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (TYPE_2__*) ; 
 struct sigqueue* malloc (int) ; 
 int /*<<< orphan*/  notify (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ signal_is_blockable (int) ; 
 int /*<<< orphan*/  sigset_add (int*,int) ; 
 scalar_t__ sigset_has (int,int) ; 
 int /*<<< orphan*/  unlock (TYPE_2__*) ; 

__attribute__((used)) static void deliver_signal_unlocked(struct task *task, int sig, struct siginfo_ info) {
    if (sigset_has(task->pending, sig))
        return;

    sigset_add(&task->pending, sig);
    struct sigqueue *sigqueue = malloc(sizeof(struct sigqueue));
    sigqueue->info = info;
    sigqueue->info.sig = sig;
    list_add_tail(&task->queue, &sigqueue->queue);

    if (sigset_has(task->blocked & ~task->waiting, sig) && signal_is_blockable(sig))
        return;

    if (task != current) {
        pthread_kill(task->thread, SIGUSR1);

        // wake up any pthread condition waiters
        // actual madness, I hope to god it's correct
        // must release the sighand lock while going insane, to avoid a deadlock
        unlock(&task->sighand->lock);
retry:
        lock(&task->waiting_cond_lock);
        if (task->waiting_cond != NULL) {
            bool mine = false;
            if (pthread_mutex_trylock(&task->waiting_lock->m) == EBUSY) {
                if (pthread_equal(task->waiting_lock->owner, pthread_self()))
                    mine = true;
                if (!mine) {
                    unlock(&task->waiting_cond_lock);
                    goto retry;
                }
            }
            notify(task->waiting_cond);
            if (!mine)
                unlock(task->waiting_lock);
        }
        unlock(&task->waiting_cond_lock);
        lock(&task->sighand->lock);
    }
}