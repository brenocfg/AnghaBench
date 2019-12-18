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
 int /*<<< orphan*/  break_btn ; 
 int /*<<< orphan*/  dtmf_tile ; 
 int /*<<< orphan*/  frame_lcd ; 
 int /*<<< orphan*/  press_btn ; 
 int /*<<< orphan*/  set_bkg_data (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bkg_tiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void init_bkg()
{
	/* Initialize the background */
	set_bkg_data( 0, 9, frame_lcd);
	set_bkg_data( 9, 9, break_btn);
	set_bkg_data(18, 9, press_btn);
	
	set_bkg_tiles(0, 0, 20, 18, dtmf_tile);
}