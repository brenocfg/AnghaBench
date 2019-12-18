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
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__ win_dest_pos_x ; 
 scalar_t__ win_dest_pos_y ; 
 scalar_t__ win_pos_x ; 
 scalar_t__ win_pos_y ; 

UBYTE UIAtDest()
{
  return win_pos_x == win_dest_pos_x && win_pos_y == win_dest_pos_y;
}