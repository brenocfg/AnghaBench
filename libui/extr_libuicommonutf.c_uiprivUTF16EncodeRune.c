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
typedef  int uint16_t ;

/* Variables and functions */
 int badrune ; 

size_t uiprivUTF16EncodeRune(uint32_t rune, uint16_t *encoded)
{
	uint16_t low, high;

	// not in the valid range for Unicode
	if (rune > 0x10FFFF)
		rune = badrune;
	// surrogate runes cannot be encoded
	if (rune >= 0xD800 && rune < 0xE000)
		rune = badrune;

	if (rune < 0x10000) {
		encoded[0] = (uint16_t) rune;
		return 1;
	}

	rune -= 0x10000;
	low = (uint16_t) (rune & 0x3FF);
	rune >>= 10;
	high = (uint16_t) (rune & 0x3FF);
	encoded[0] = high | 0xD800;
	encoded[1] = low | 0xDC00;
	return 2;
}