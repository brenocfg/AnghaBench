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
typedef  scalar_t__ UBYTE ;

/* Variables and functions */
 scalar_t__ win_dest_pos_x ; 
 scalar_t__ win_dest_pos_y ; 
 scalar_t__ win_pos_x ; 
 scalar_t__ win_pos_y ; 
 scalar_t__ win_speed ; 

void UIMoveTo(UBYTE x, UBYTE y, UBYTE speed)
{
  win_dest_pos_x = x;
  win_dest_pos_y = y;
  if (speed == 0)
  {
    win_pos_x = x;
    win_pos_y = y;
  }
  else
  {
    win_speed = speed;
  }
}