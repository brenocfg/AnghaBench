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
 scalar_t__ CGB_TYPE ; 
 int /*<<< orphan*/  DEF_SP ; 
 int /*<<< orphan*/  SHOW_BKG ; 
 int /*<<< orphan*/  SHOW_SPRITES ; 
 int /*<<< orphan*/  SPRITES_8x8 ; 
 scalar_t__ _cpu ; 
 int /*<<< orphan*/  bkg ; 
 int /*<<< orphan*/  bkg_c ; 
 int /*<<< orphan*/  bkg_m ; 
 int /*<<< orphan*/ * bkg_p ; 
 int /*<<< orphan*/  fore ; 
 int /*<<< orphan*/  move_sprite (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_1up ; 
 int /*<<< orphan*/  msg_lv ; 
 int /*<<< orphan*/ * obj_p ; 
 int pw ; 
 int /*<<< orphan*/  set_bkg_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bkg_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bkg_palette (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bkg_tiles (int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_palette (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sprite_tile (int,int /*<<< orphan*/ ) ; 

void init_screen()
{
  UBYTE n;

  if( _cpu==CGB_TYPE ) {
    /* Transfer color palette */
    set_bkg_palette( 0, 1, &bkg_p[0] );
    set_bkg_palette( 1, 1, &bkg_p[4] );
    set_bkg_palette( 2, 1, &bkg_p[8] );
    set_bkg_palette( 3, 1, &bkg_p[12] );
    set_bkg_palette( 4, 1, &bkg_p[16] );
    set_bkg_palette( 5, 1, &bkg_p[20] );
    set_bkg_palette( 6, 1, &bkg_p[24] );
    set_bkg_palette( 7, 1, &bkg_p[28] );
    set_sprite_palette( 0, 1, &obj_p[0] );
    set_sprite_palette( 1, 1, &obj_p[4] );
    set_sprite_palette( 2, 1, &obj_p[8] );
    set_sprite_palette( 3, 1, &obj_p[12] );
    set_sprite_palette( 4, 1, &obj_p[16] );
    set_sprite_palette( 5, 1, &obj_p[20] );
    set_sprite_palette( 6, 1, &obj_p[24] );
    set_sprite_palette( 7, 1, &obj_p[28] );

    /* set attributes */
    set_bkg_attr( 0, 0, 20, 18, bkg_c );
    set_bkg_tiles(  0, 0, 20, 18, bkg_c );
  } else {
    set_bkg_tiles(  0, 0, 20, 18, bkg_m );
  }

  pw = 50;
  set_bkg_data(  0, 96, bkg );
  set_bkg_tiles(  0, 0, 3, 1, msg_1up );
  set_bkg_tiles( 16, 0, 2, 1, msg_lv );
  SHOW_BKG;
  SPRITES_8x8;
  set_sprite_data( 0, 128, fore );
  SHOW_SPRITES;
  for( n=0; n<40; n++ ) {
    set_sprite_tile( n, DEF_SP );
    move_sprite( n, 0, 0 );
  }
}