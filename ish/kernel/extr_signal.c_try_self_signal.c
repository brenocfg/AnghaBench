#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sighand {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  blocked; struct sighand* sighand; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINFO_NIL ; 
 scalar_t__ SIGNAL_IGNORE ; 
 int SIGTTIN_ ; 
 int SIGTTOU_ ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  deliver_signal_unlocked (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_action (struct sighand*,int) ; 
 int /*<<< orphan*/  sigset_has (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

bool try_self_signal(int sig) {
    assert(sig == SIGTTIN_ || sig == SIGTTOU_);

    struct sighand *sighand = current->sighand;
    lock(&sighand->lock);
    bool can_send = signal_action(sighand, sig) != SIGNAL_IGNORE &&
        !sigset_has(current->blocked, sig);
    if (can_send)
        deliver_signal_unlocked(current, sig, SIGINFO_NIL);
    unlock(&sighand->lock);
    return can_send;
}