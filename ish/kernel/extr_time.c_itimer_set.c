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
typedef  int /*<<< orphan*/  timer_callback_t ;
struct timer_spec {int dummy; } ;
struct timer {int dummy; } ;
struct tgroup {struct timer* timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 scalar_t__ IS_ERR (struct timer*) ; 
 int ITIMER_REAL_ ; 
 int PTR_ERR (struct timer*) ; 
 int _EINVAL ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ itimer_notify ; 
 struct timer* timer_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int timer_set (struct timer*,struct timer_spec,struct timer_spec*) ; 

__attribute__((used)) static int itimer_set(struct tgroup *group, int which, struct timer_spec spec, struct timer_spec *old_spec) {
    if (which != ITIMER_REAL_) {
        FIXME("unimplemented setitimer %d", which);
        return _EINVAL;
    }

    if (!group->timer) {
        struct timer *timer = timer_new((timer_callback_t) itimer_notify, current);
        if (IS_ERR(timer))
            return PTR_ERR(timer);
        group->timer = timer;
    }

    return timer_set(group->timer, spec, old_spec);
}