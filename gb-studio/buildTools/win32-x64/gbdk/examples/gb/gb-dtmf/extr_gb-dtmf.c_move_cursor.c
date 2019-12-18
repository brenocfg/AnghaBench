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
 int /*<<< orphan*/  move_sprite (int,scalar_t__,scalar_t__) ; 

void move_cursor(UBYTE x, UBYTE y)
{
	move_sprite(23, x, y);
	move_sprite(24, x, y+8);
	move_sprite(25, x+8, y);
	move_sprite(26, x+8, y+8);
}