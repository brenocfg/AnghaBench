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
 int /*<<< orphan*/  DISPLAY_ON ; 
 int /*<<< orphan*/  SHOW_BKG ; 
 int VBK_REG ; 
 int /*<<< orphan*/  bar_a ; 
 int /*<<< orphan*/  bar_c ; 
 int /*<<< orphan*/  bar_m ; 
 int /*<<< orphan*/  bar_mHeight ; 
 int /*<<< orphan*/  bar_mWidth ; 
 int /*<<< orphan*/ * bar_p ; 
 int /*<<< orphan*/  enable_interrupts () ; 
 int /*<<< orphan*/  set_bkg_data (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bkg_palette (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bkg_tiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void)
{
  /* Transfer color palettes */
  set_bkg_palette( 7, 1, &bar_p[0] );
  set_bkg_palette( 6, 1, &bar_p[4] );
  set_bkg_palette( 5, 1, &bar_p[8] );
  set_bkg_palette( 4, 1, &bar_p[12] );
  set_bkg_palette( 3, 1, &bar_p[16] );
  set_bkg_palette( 2, 1, &bar_p[20] );
  set_bkg_palette( 1, 1, &bar_p[24] );
  set_bkg_palette( 0, 1, &bar_p[28] );

  /* CHR code transfer */
  set_bkg_data( 0x0, 32, bar_c );

  /* Select VRAM bank 1 */
  VBK_REG = 1;
  /* Set attributes */
  set_bkg_tiles( 0, 0, bar_mWidth, bar_mHeight, bar_a );

  /* Select VRAM bank 0 */
  VBK_REG = 0;
  /* Set data */
  set_bkg_tiles( 0, 0, bar_mWidth, bar_mHeight, bar_m );

  SHOW_BKG;
  enable_interrupts();
  DISPLAY_ON;

  return 0;
}