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
 int /*<<< orphan*/  LCD_HIGHT ; 
 int /*<<< orphan*/  LCD_WIDTH ; 
 int /*<<< orphan*/  LCD_X ; 
 int /*<<< orphan*/  LCD_Y ; 
 int /*<<< orphan*/  OFFSET ; 
 int /*<<< orphan*/  dtmf_lcd ; 
 int /*<<< orphan*/  init_disp ; 
 int /*<<< orphan*/  set_bkg_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bkg_tiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clr_disp()
{
	set_bkg_data(OFFSET, 50, dtmf_lcd);
	set_bkg_tiles(LCD_X, LCD_Y, LCD_WIDTH, LCD_HIGHT, init_disp);
}