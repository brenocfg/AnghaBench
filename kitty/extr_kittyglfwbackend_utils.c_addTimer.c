#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_callback_func ;
typedef  scalar_t__ id_type ;
struct TYPE_5__ {double interval; char const* name; int repeats; scalar_t__ id; int /*<<< orphan*/  free; void* callback_data; int /*<<< orphan*/  callback; scalar_t__ trigger_at; } ;
typedef  TYPE_1__ Timer ;
struct TYPE_6__ {int timers_count; TYPE_1__* timers; } ;
typedef  int /*<<< orphan*/  GLFWuserdatafreefun ;
typedef  TYPE_2__ EventLoopData ;

/* Variables and functions */
 scalar_t__ DBL_MAX ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ monotonic () ; 
 scalar_t__ timer_counter ; 
 int /*<<< orphan*/  update_timers (TYPE_2__*) ; 

id_type
addTimer(EventLoopData *eld, const char *name, double interval, int enabled, bool repeats, timer_callback_func cb, void *cb_data, GLFWuserdatafreefun free) {
    if (eld->timers_count >= sizeof(eld->timers)/sizeof(eld->timers[0])) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Too many timers added");
        return 0;
    }
    Timer *t = eld->timers + eld->timers_count++;
    t->interval = interval;
    t->name = name;
    t->trigger_at = enabled ? monotonic() + interval : DBL_MAX;
    t->repeats = repeats;
    t->callback = cb;
    t->callback_data = cb_data;
    t->free = free;
    t->id = ++timer_counter;
    update_timers(eld);
    return timer_counter;
}