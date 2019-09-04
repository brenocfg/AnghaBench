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
typedef  int /*<<< orphan*/  watch_callback_func ;
typedef  scalar_t__ id_type ;
struct TYPE_5__ {char const* name; int fd; int events; int enabled; scalar_t__ id; int /*<<< orphan*/ * free; void* callback_data; int /*<<< orphan*/  callback; } ;
typedef  TYPE_1__ Watch ;
struct TYPE_6__ {int watches_count; TYPE_1__* watches; } ;
typedef  TYPE_2__ EventLoopData ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_fds (TYPE_2__*) ; 
 scalar_t__ watch_counter ; 

id_type
addWatch(EventLoopData *eld, const char* name, int fd, int events, int enabled, watch_callback_func cb, void *cb_data) {
    if (eld->watches_count >= sizeof(eld->watches)/sizeof(eld->watches[0])) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Too many watches added");
        return 0;
    }
    Watch *w = eld->watches + eld->watches_count++;
    w->name = name;
    w->fd = fd; w->events = events; w->enabled = enabled;
    w->callback = cb;
    w->callback_data = cb_data;
    w->free = NULL;
    w->id = ++watch_counter;
    update_fds(eld);
    return w->id;
}