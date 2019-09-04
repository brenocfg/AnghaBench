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
typedef  int /*<<< orphan*/  timer_callback_fun ;
typedef  int /*<<< orphan*/  id_type ;

/* Variables and functions */
 int /*<<< orphan*/  glfwAddTimer (double,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

id_type
add_main_loop_timer(double interval, bool repeats, timer_callback_fun callback, void *callback_data, timer_callback_fun free_callback) {
    return glfwAddTimer(interval, repeats, callback, callback_data, free_callback);
}