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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int do_redraw ; 
 int height ; 
 int width ; 

__attribute__((used)) static void framebufferSizeFun(GLFWwindow* window, int w, int h)
{
    width  = w;
    height = h > 0 ? h : 1;
    do_redraw = 1;
}