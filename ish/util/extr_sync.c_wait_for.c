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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  lock_t ;
typedef  int /*<<< orphan*/  cond_t ;

/* Variables and functions */
 int _EINTR ; 
 int _ETIMEDOUT ; 
 scalar_t__ is_signal_pending (int /*<<< orphan*/ *) ; 
 int wait_for_ignore_signals (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 

int wait_for(cond_t *cond, lock_t *lock, struct timespec *timeout) {
    if (is_signal_pending(lock))
        return _EINTR;
    int err = wait_for_ignore_signals(cond, lock, timeout);
    if (err < 0)
        return _ETIMEDOUT;
    if (is_signal_pending(lock))
        return _EINTR;
    return 0;
}