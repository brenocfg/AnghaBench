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
 int /*<<< orphan*/  BGP_REG ; 
 scalar_t__ CGB_TYPE ; 
 int /*<<< orphan*/  OBP0_REG ; 
 scalar_t__ _cpu ; 
 int /*<<< orphan*/ * bgp_fade_vals ; 
 int /*<<< orphan*/  custom_bg_pal ; 
 int /*<<< orphan*/  custom_bg_pal_fade_step1 ; 
 int /*<<< orphan*/  custom_bg_pal_fade_step2 ; 
 int /*<<< orphan*/  custom_bg_pal_fade_step3 ; 
 int /*<<< orphan*/  custom_bg_pal_fade_step4 ; 
 int /*<<< orphan*/  custom_spr1_pal ; 
 int /*<<< orphan*/  custom_spr1_pal_fade_step1 ; 
 int /*<<< orphan*/  custom_spr1_pal_fade_step2 ; 
 int /*<<< orphan*/  custom_spr1_pal_fade_step3 ; 
 int /*<<< orphan*/  custom_spr1_pal_fade_step4 ; 
 int /*<<< orphan*/ * obj_fade_vals ; 
 int /*<<< orphan*/  set_bkg_palette (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sprite_palette (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ApplyPaletteChange(UBYTE index)
{
  #ifdef CUSTOM_COLORS
  if (_cpu == CGB_TYPE) {
    if (index == 0 || index == 1)
    {
      set_bkg_palette(0, 1, custom_bg_pal_fade_step4);
      set_sprite_palette(0, 1, custom_spr1_pal_fade_step4);
    } 
    else if (index == 2)
    {
      set_bkg_palette(0, 1, custom_bg_pal_fade_step3);
      set_sprite_palette(0, 1, custom_spr1_pal_fade_step3);
    }
    else if (index == 3)
    {
      set_bkg_palette(0, 1, custom_bg_pal_fade_step2);
      set_sprite_palette(0, 1, custom_spr1_pal_fade_step2);
    }
    else if (index == 4)
    {
      set_bkg_palette(0, 1, custom_bg_pal_fade_step1);
      set_sprite_palette(0, 1, custom_spr1_pal_fade_step1);
    }
    else if (index == 5)
    {
      set_bkg_palette(0, 1, custom_bg_pal);
      set_sprite_palette(0, 1, custom_spr1_pal);
    }
  } 
  else 
  #endif
  {
    OBP0_REG = obj_fade_vals[index];
    BGP_REG = bgp_fade_vals[index];
  }
}