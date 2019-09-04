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
typedef  int /*<<< orphan*/  GLFWuserdatafun ;

/* Variables and functions */
 unsigned long long _glfwPlatformAddTimer (double,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

unsigned long long glfwAddTimer(
        double interval, bool repeats, GLFWuserdatafun callback,
        void *callback_data, GLFWuserdatafun free_callback)
{
    return _glfwPlatformAddTimer(interval, repeats, callback, callback_data, free_callback);
}