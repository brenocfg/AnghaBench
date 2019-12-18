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
struct TYPE_2__ {int x; int w; int y; int h; } ;

/* Variables and functions */
 TYPE_1__* icons ; 
 size_t menu_cursor_pos ; 
 int /*<<< orphan*/  move_sprite (int /*<<< orphan*/ ,int,int) ; 

void move_menu_cursor()
{
  move_sprite(0,
	      ((icons[menu_cursor_pos].x+icons[menu_cursor_pos].w)<<3) + 4,
	      ((icons[menu_cursor_pos].y+icons[menu_cursor_pos].h)<<3) + 12);
}