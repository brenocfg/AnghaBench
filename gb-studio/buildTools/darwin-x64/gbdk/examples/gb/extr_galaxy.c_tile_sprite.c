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
typedef  size_t UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/ * earth_tiles ; 
 int /*<<< orphan*/  set_sprite_tile (int,int /*<<< orphan*/ ) ; 
 int sframe ; 

void tile_sprite()
{
  UBYTE s;

  s = sframe<<1;
  set_sprite_tile(0, earth_tiles[s]);
  set_sprite_tile(1, earth_tiles[s+1]);
}