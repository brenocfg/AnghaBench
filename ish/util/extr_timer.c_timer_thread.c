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
struct timer {int running; int /*<<< orphan*/  lock; scalar_t__ dead; struct timespec interval; int /*<<< orphan*/  start; int /*<<< orphan*/  end; int /*<<< orphan*/  data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct timer*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec_add (int /*<<< orphan*/ ,struct timespec) ; 
 int /*<<< orphan*/  timespec_now () ; 
 scalar_t__ timespec_positive (struct timespec) ; 
 struct timespec timespec_subtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *timer_thread(void *param) {
    struct timer *timer = param;
    lock(&timer->lock);
    while (true) {
        struct timespec remaining = timespec_subtract(timer->end, timespec_now());
        while (timer->running && timespec_positive(remaining)) {
            unlock(&timer->lock);
            nanosleep(&remaining, NULL);
            lock(&timer->lock);
            remaining = timespec_subtract(timer->end, timespec_now());
        }
        if (timer->running)
            timer->callback(timer->data);
        if (timespec_positive(timer->interval)) {
            timer->start = timer->end;
            timer->end = timespec_add(timer->start, timer->interval);
        } else {
            break;
        }
    }
    timer->running = false;
    if (timer->dead)
        free(timer);
    else
        unlock(&timer->lock);
    return NULL;
}