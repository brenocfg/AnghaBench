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
 int /*<<< orphan*/  cursor_data ; 
 int /*<<< orphan*/  set_sprite_data (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_tile (int,int) ; 

void init_cursor()
{
	UBYTE i;

	/* Setup the cursor data*/
	set_sprite_data(23, 8, cursor_data);

	for(i = 23;i <= 30;i++){
		set_sprite_tile(i, i);
	}
}