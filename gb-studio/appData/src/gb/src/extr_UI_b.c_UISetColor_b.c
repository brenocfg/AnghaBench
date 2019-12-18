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
 int /*<<< orphan*/  set_bkg_data (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_win_tiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_black ; 
 int /*<<< orphan*/ * ui_colors ; 
 int /*<<< orphan*/  ui_white ; 

void UISetColor_b(UBYTE color)
{
  // Not sure why need to set_bkg_data again but this doesn't
  // work in rom without reseting here
  set_bkg_data(0xC9, 1, ui_white);
  set_bkg_data(0xCA, 1, ui_black);
  set_win_tiles(0, 0, 20, 18, ui_colors[color]);
}