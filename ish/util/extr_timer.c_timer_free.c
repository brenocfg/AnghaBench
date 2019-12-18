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
struct timer {int running; int dead; int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  free (struct timer*) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

void timer_free(struct timer *timer) {
    lock(&timer->lock);
    if (timer->running) {
        timer->running = false;
        timer->dead = true;
        pthread_kill(timer->thread, SIGUSR1);
        unlock(&timer->lock);
    } else {
        unlock(&timer->lock);
        if (!timer->dead)
            free(timer);
    }
}