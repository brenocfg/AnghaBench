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
typedef  int UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  set_bkg_tiles (int,int /*<<< orphan*/ ,int,int,unsigned char*) ; 

void show_score( UWORD s )
{
  UWORD m;
  UBYTE i, n, f;
  unsigned char score[6];

  f = 0; m = 10000;
  for( i=0; i<5; i++ ) {
    n = s/m; s = s%m; m = m/10;
    if( (n==0)&&(f==0) ) {
      score[i] = 0x20;      /* ' ' */
    } else {
      f = 1;
      score[i] = 0x30+n;    /* '0' - '9' */
    }
  }
  score[5] = 0x30;      /* '0' */
  set_bkg_tiles( 4, 0, 6, 1, score );
}