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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

int
nsecbitmap_has_type_rdata(uint8_t* bitmap, size_t len, uint16_t type)
{
	/* Check type present in NSEC typemap with bitmap arg */
	/* bitmasks for determining type-lowerbits presence */
	uint8_t masks[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	uint8_t type_window = type>>8;
	uint8_t type_low = type&0xff;
	uint8_t win, winlen;
	/* read each of the type bitmap windows and see if the searched
	 * type is amongst it */
	while(len > 0) {
		if(len < 3) /* bad window, at least window# winlen bitmap */
			return 0;
		win = *bitmap++;
		winlen = *bitmap++;
		len -= 2;
		if(len < winlen || winlen < 1 || winlen > 32) 
			return 0;	/* bad window length */
		if(win == type_window) {
			/* search window bitmap for the correct byte */
			/* mybyte is 0 if we need the first byte */
			size_t mybyte = type_low>>3;
			if(winlen <= mybyte)
				return 0; /* window too short */
			return (int)(bitmap[mybyte] & masks[type_low&0x7]);
		} else {
			/* not the window we are looking for */
			bitmap += winlen;
			len -= winlen;
		}
	}
	/* end of bitmap reached, no type found */
	return 0;
}