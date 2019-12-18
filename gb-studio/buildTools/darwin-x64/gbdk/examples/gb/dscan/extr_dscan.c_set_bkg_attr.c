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
 int VBK_REG ; 
 int /*<<< orphan*/ * bkgCGB ; 
 int /*<<< orphan*/ * msg_tile ; 
 int /*<<< orphan*/  set_bkg_tiles (scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *) ; 

void set_bkg_attr( UBYTE x, UBYTE y, UBYTE sx, UBYTE sy, unsigned char *d )
{
  UBYTE xx, yy;

  VBK_REG = 1;		/* select palette bank */
  for( yy=0; yy<sy; yy++ ) {
    for( xx=0; xx<sx; xx++ ) {
      msg_tile[xx] = bkgCGB[(unsigned int)*d];
      d++;
    }
    set_bkg_tiles( x, y+yy, sx, 1, msg_tile );
  }
  VBK_REG = 0;		/* select data bank */
}