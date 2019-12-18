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
struct timespec {int tv_nsec; int tv_sec; } ;
struct TYPE_2__ {scalar_t__ p_frame; scalar_t__ d_frame; int /*<<< orphan*/  p_done; int /*<<< orphan*/  particles_lock; int /*<<< orphan*/  dt; int /*<<< orphan*/  t; int /*<<< orphan*/  d_done; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  cnd_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnd_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  particle_engine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ thread_sync ; 

__attribute__((used)) static int physics_thread_main(void* arg)
{
    GLFWwindow* window = arg;

    for (;;)
    {
        mtx_lock(&thread_sync.particles_lock);

        // Wait for particle drawing to be done
        while (!glfwWindowShouldClose(window) &&
               thread_sync.p_frame > thread_sync.d_frame)
        {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_nsec += 100 * 1000 * 1000;
            ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
            ts.tv_nsec %= 1000 * 1000 * 1000;
            cnd_timedwait(&thread_sync.d_done, &thread_sync.particles_lock, &ts);
        }

        if (glfwWindowShouldClose(window))
            break;

        // Update particles
        particle_engine(thread_sync.t, thread_sync.dt);

        // Update frame counter
        thread_sync.p_frame++;

        // Unlock mutex and signal drawing thread
        mtx_unlock(&thread_sync.particles_lock);
        cnd_signal(&thread_sync.p_done);
    }

    return 0;
}