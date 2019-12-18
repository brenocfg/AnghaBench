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
typedef  int UBYTE ;
struct TYPE_2__ {int w; int h; scalar_t__ hot_y; scalar_t__ hot_x; } ;

/* Variables and functions */
 size_t current_cursor ; 
 scalar_t__ cursor_x ; 
 scalar_t__ cursor_y ; 
 TYPE_1__* cursors ; 
 int /*<<< orphan*/  move_sprite (int,scalar_t__,scalar_t__) ; 

void move_cursor()
{
  UBYTE x, y;

  for(x = 0; x < cursors[current_cursor].w; x++)
    for(y = 0; y < cursors[current_cursor].h; y++)
      move_sprite((x<<1)+y,
		  cursor_x+8 - cursors[current_cursor].hot_x + (x<<3),
		  cursor_y+16 - cursors[current_cursor].hot_y + (y<<3));
}