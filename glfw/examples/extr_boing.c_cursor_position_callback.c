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
 float cursor_x ; 
 float cursor_y ; 
 scalar_t__ override_pos ; 
 int /*<<< orphan*/  set_ball_pos (float,float) ; 

void cursor_position_callback( GLFWwindow* window, double x, double y )
{
   cursor_x = (float) x;
   cursor_y = (float) y;

   if ( override_pos )
      set_ball_pos(cursor_x, cursor_y);
}