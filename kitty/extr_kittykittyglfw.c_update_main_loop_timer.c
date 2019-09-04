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
typedef  int /*<<< orphan*/  id_type ;

/* Variables and functions */
 int /*<<< orphan*/  glfwUpdateTimer (int /*<<< orphan*/ ,double,int) ; 

void
update_main_loop_timer(id_type timer_id, double interval, bool enabled) {
    glfwUpdateTimer(timer_id, interval, enabled);
}