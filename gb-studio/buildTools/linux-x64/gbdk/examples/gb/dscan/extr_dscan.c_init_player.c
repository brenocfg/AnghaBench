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

/* Variables and functions */
 scalar_t__ DEF_PX ; 
 int /*<<< orphan*/  DEF_PY ; 
 int /*<<< orphan*/ * foreCGB ; 
 int /*<<< orphan*/  move_sprite (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pf ; 
 scalar_t__ px ; 
 int /*<<< orphan*/  set_sprite_attrb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_tile (int,int) ; 

void init_player()
{
  pf = 0; px = DEF_PX;
  set_sprite_tile( 0, 0 );
  set_sprite_attrb( 0, foreCGB[0] );
  move_sprite( 0, px, DEF_PY );
  set_sprite_tile( 1, 1 );
  set_sprite_attrb( 1, foreCGB[1] );
  move_sprite( 1, px+8, DEF_PY );
}