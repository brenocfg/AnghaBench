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
typedef  scalar_t__ UBYTE ;
struct TYPE_2__ {scalar_t__ w; scalar_t__ h; scalar_t__ data_idx; } ;

/* Variables and functions */
 size_t current_cursor ; 
 TYPE_1__* cursors ; 
 int /*<<< orphan*/ * cursors_data ; 
 int /*<<< orphan*/  move_sprite (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_data (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_prop (scalar_t__,int) ; 
 int /*<<< orphan*/  set_sprite_tile (scalar_t__,scalar_t__) ; 

void set_cursor()
{
    UBYTE x, y, i;

    i = 0;
    for(x = 0; x < cursors[current_cursor].w; x++)
	for(y = 0; y < cursors[current_cursor].h; y++) {
	    set_sprite_data(i,
			    1,
			    cursors_data[cursors[current_cursor].data_idx+i]);
	    set_sprite_tile(i, i);
	    set_sprite_prop(i, 0x10);
	    i++;
	}
    /* Hide unused sprites */
    for(; i < 4; i++) {
	move_sprite(i, 0, 0);
    }
}