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
struct timer_spec {int /*<<< orphan*/  value; int /*<<< orphan*/  interval; } ;
struct timer {int running; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; int /*<<< orphan*/  interval; struct timespec start; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timer*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_thread ; 
 int /*<<< orphan*/  timespec_add (struct timespec,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec_is_zero (int /*<<< orphan*/ ) ; 
 struct timespec timespec_now () ; 
 int /*<<< orphan*/  timespec_subtract (int /*<<< orphan*/ ,struct timespec) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

int timer_set(struct timer *timer, struct timer_spec spec, struct timer_spec *oldspec) {
    lock(&timer->lock);
    struct timespec now = timespec_now();
    if (oldspec != NULL) {
        oldspec->value = timespec_subtract(timer->end, now);
        oldspec->interval = timer->interval;
    }

    timer->start = now;
    timer->end = timespec_add(timer->start, spec.value);
    timer->interval = spec.interval;
    if (!timespec_is_zero(spec.value)) {
        if (!timer->running) {
            timer->running = true;
            pthread_create(&timer->thread, NULL, timer_thread, timer);
            pthread_detach(timer->thread);
        }
    } else {
        if (timer->running) {
            timer->running = false;
            pthread_kill(timer->thread, SIGUSR1);
        }
    }
    unlock(&timer->lock);
    return 0;
}