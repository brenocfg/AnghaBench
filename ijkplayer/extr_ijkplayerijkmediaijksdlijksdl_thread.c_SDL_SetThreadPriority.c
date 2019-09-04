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
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  scalar_t__ SDL_ThreadPriority ;

/* Variables and functions */
 int /*<<< orphan*/  ALOGE (char*) ; 
 scalar_t__ SDL_THREAD_PRIORITY_HIGH ; 
 scalar_t__ SDL_THREAD_PRIORITY_LOW ; 
 scalar_t__ pthread_getschedparam (int /*<<< orphan*/ ,int*,struct sched_param*) ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ pthread_setschedparam (int /*<<< orphan*/ ,int,struct sched_param*) ; 
 void* sched_get_priority_max (int) ; 
 void* sched_get_priority_min (int) ; 

int SDL_SetThreadPriority(SDL_ThreadPriority priority)
{
    struct sched_param sched;
    int policy;
    pthread_t thread = pthread_self();

    if (pthread_getschedparam(thread, &policy, &sched) < 0) {
        ALOGE("pthread_getschedparam() failed");
        return -1;
    }
    if (priority == SDL_THREAD_PRIORITY_LOW) {
        sched.sched_priority = sched_get_priority_min(policy);
    } else if (priority == SDL_THREAD_PRIORITY_HIGH) {
        sched.sched_priority = sched_get_priority_max(policy);
    } else {
        int min_priority = sched_get_priority_min(policy);
        int max_priority = sched_get_priority_max(policy);
        sched.sched_priority = (min_priority + (max_priority - min_priority) / 2);
    }
    if (pthread_setschedparam(thread, policy, &sched) < 0) {
        ALOGE("pthread_setschedparam() failed");
        return -1;
    }
    return 0;
}