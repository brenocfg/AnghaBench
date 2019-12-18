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
typedef  int UINT16 ;
typedef  int UBYTE ;

/* Variables and functions */
 int DEF_PC0 ; 
 int DEF_PC1 ; 
 int DEF_PF ; 
 int /*<<< orphan*/  DEF_PY ; 
 int DEF_SP ; 
 int DIV_REG ; 
 int J_DOWN ; 
 int J_LEFT ; 
 int J_RIGHT ; 
 int J_SELECT ; 
 int J_START ; 
 int J_UP ; 
 scalar_t__ MAX_PX ; 
 int MAX_TT ; 
 scalar_t__ MIN_PX ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/ * foreCGB ; 
 int /*<<< orphan*/  hide_msg () ; 
 int /*<<< orphan*/  init_enemy () ; 
 int /*<<< orphan*/  init_kirai () ; 
 int /*<<< orphan*/  init_player () ; 
 int /*<<< orphan*/  init_score () ; 
 int /*<<< orphan*/  init_tama () ; 
 int /*<<< orphan*/  initarand (int) ; 
 int joypad () ; 
 int k_left ; 
 int k_right ; 
 int /*<<< orphan*/  move_sprite (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int pf ; 
 int pl ; 
 int ps ; 
 int pw ; 
 scalar_t__ px ; 
 int /*<<< orphan*/  set_sprite_attrb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_tile (int,int) ; 
 int /*<<< orphan*/  show_gover () ; 
 int /*<<< orphan*/  show_level (int) ; 
 int /*<<< orphan*/  show_pause () ; 
 int /*<<< orphan*/  show_score (int) ; 
 int* tf ; 
 scalar_t__* tx ; 
 int /*<<< orphan*/ * ty ; 
 int /*<<< orphan*/  waitpadup () ; 

void player()
{
  UBYTE key;
  UBYTE i;
  UINT16 seed;

  key = joypad();
  /* pause */
  if( key & J_START ) {
    if( pf == DEF_PF ) {
      /* Initialize the random number generator */
      seed = DIV_REG;
      waitpadup();
      seed |= ((UINT16)DIV_REG << 8);
      initarand(seed);
      hide_msg();
      init_score();
      init_player();
      init_tama();
      init_enemy();
      init_kirai();
      delay( 500 );
    } else {
      show_pause();
      waitpadup();
      key = joypad();
      while( !(key & J_START) ) {
        key = joypad();
        if( key & J_DOWN ) {
          if(pl > 0)
            pl--;
          show_level( pl );
          waitpadup();
        } else if( key & J_UP ) {
          if(pl < 8)
            pl++;
          show_level( pl );
          waitpadup();
        } else if( key & J_LEFT ) {
          while( joypad() & J_LEFT ) {
            if(pw > 0)
              pw--;
            show_score( pw );
            delay( 250 );
          }
          show_score( ps );
        } else if( key & J_RIGHT ) {
          while( joypad() & J_RIGHT ) {
            if(pw < 99)
              pw++;
            show_score( pw );
            delay( 250 );
          }
          show_score( ps );
        } else if( key & J_SELECT ) {
          i = k_right;
          k_right = k_left;
          k_left  = i;
          waitpadup();
        }
      }
      waitpadup();
      hide_msg();
      delay( 500 );
    }
    return;
  }

  /* dead */
  if( pf > 1 ) {
    if( pf < DEF_PF ) {
      set_sprite_tile( 0, pf*2+DEF_PC0 );
      set_sprite_attrb( 0, foreCGB[pf*2+DEF_PC0] );
      set_sprite_tile( 1, pf*2+DEF_PC1 );
      set_sprite_attrb( 1, foreCGB[pf*2+DEF_PC1] );
      pf++;
    } else {
      set_sprite_tile( 0, DEF_SP );
      set_sprite_tile( 1, DEF_SP );
      show_gover();
    }
    return;
  }

  /* move */
  if( (key&J_LEFT)&&(px>MIN_PX) ) {
    px--;
    move_sprite( 0, px, DEF_PY ); move_sprite( 1, px+8, DEF_PY );
  } else if( (key&J_RIGHT)&&(px<MAX_PX) ) {
    px++;
    move_sprite( 0, px, DEF_PY ); move_sprite( 1, px+8, DEF_PY );
  }
  /* shot */
  if( key & k_left ) {  /* change J_B to J_A */
    if( pf == 0 ) {
      pf = 1;
      for( i=0; i<MAX_TT; i++ ) {
        if( tf[i] == 0 ) {
          tf[i] = 1; tx[i] = px-4; ty[i] = DEF_PY;
          break;
        }
      }
    }
  } else if( key & k_right ) {  /* change J_A to J_B */
    if( pf == 0 ) {
      pf = 1;
      for( i=0; i<MAX_TT; i++ ) {
        if( tf[i] == 0 ) {
          tf[i] = 1; tx[i] = px+12; ty[i] = DEF_PY;
          break;
        }
      }
    }
  } else if( pf == 1 ) {
    pf = 0;
  }
}