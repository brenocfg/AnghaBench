#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timer_spec {TYPE_4__ value; TYPE_2__ interval; } ;
struct tgroup {int /*<<< orphan*/  lock; } ;
struct TYPE_8__ {int usec; int /*<<< orphan*/  sec; } ;
struct TYPE_6__ {int usec; int /*<<< orphan*/  sec; } ;
struct itimerval_ {TYPE_3__ value; TYPE_1__ interval; } ;
typedef  int int_t ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_10__ {struct tgroup* group; } ;

/* Variables and functions */
 int /*<<< orphan*/  STRACE (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int _EFAULT ; 
 TYPE_5__* current ; 
 int itimer_set (struct tgroup*,int,struct timer_spec,struct timer_spec*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ user_get (int /*<<< orphan*/ ,struct itimerval_) ; 
 scalar_t__ user_put (int /*<<< orphan*/ ,struct itimerval_) ; 

int_t sys_setitimer(int_t which, addr_t new_val_addr, addr_t old_val_addr) {
    struct itimerval_ val;
    if (user_get(new_val_addr, val))
        return _EFAULT;
    STRACE("setitimer(%d, {%ds %dus, %ds %dus}, 0x%x)", which, val.value.sec, val.value.usec, val.interval.sec, val.interval.usec, old_val_addr);

    struct timer_spec spec = {
        .interval.tv_sec = val.interval.sec,
        .interval.tv_nsec = val.interval.usec * 1000,
        .value.tv_sec = val.value.sec,
        .value.tv_nsec = val.value.usec * 1000,
    };
    struct timer_spec old_spec;

    struct tgroup *group = current->group;
    lock(&group->lock);
    int err = itimer_set(group, which, spec, &old_spec);
    unlock(&group->lock);
    if (err < 0)
        return err;

    if (old_val_addr != 0) {
        struct itimerval_ old_val;
        old_val.interval.sec = old_spec.interval.tv_sec;
        old_val.interval.usec = old_spec.interval.tv_nsec / 1000;
        old_val.value.sec = old_spec.value.tv_sec;
        old_val.value.usec = old_spec.value.tv_nsec / 1000;
        if (user_put(old_val_addr, old_val))
            return _EFAULT;
    }

    return 0;
}