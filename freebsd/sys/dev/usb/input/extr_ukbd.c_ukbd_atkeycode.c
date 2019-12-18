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
typedef  int uint32_t ;

/* Variables and functions */
 size_t KEY_INDEX (int) ; 
 int MOD_ALT_L ; 
 int MOD_ALT_R ; 
 int* ukbd_trtab ; 

__attribute__((used)) static uint32_t
ukbd_atkeycode(int usbcode, int shift)
{
	uint32_t keycode;

	keycode = ukbd_trtab[KEY_INDEX(usbcode)];
	/*
	 * Translate Alt-PrintScreen to SysRq.
	 *
	 * Some or all AT keyboards connected through USB have already
	 * mapped Alted PrintScreens to an unusual usbcode (0x8a).
	 * ukbd_trtab translates this to 0x7e, and key2scan() would
	 * translate that to 0x79 (Intl' 4).  Assume that if we have
	 * an Alted 0x7e here then it actually is an Alted PrintScreen.
	 *
	 * The usual usbcode for all PrintScreens is 0x46.  ukbd_trtab
	 * translates this to 0x5c, so the Alt check to classify 0x5c
	 * is routine.
	 */
	if ((keycode == 0x5c || keycode == 0x7e) &&
	    shift & (MOD_ALT_L | MOD_ALT_R))
		return (0x54);
	return (keycode);
}