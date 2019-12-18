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

const uint16_t *uiprivUTF16DecodeRune(const uint16_t *s, size_t nElem, uint32_t *rune)
{
	uint16_t high, low;

	if (*s < 0xD800 || *s >= 0xE000) {
		// self-representing character
		*rune = *s;
		s++;
		return s;
	}
	if (*s >= 0xDC00) {
		// out-of-order surrogates
		*rune = badrune;
		s++;
		return s;
	}
	if (nElem == 1) {		// not enough elements
		*rune = badrune;
		s++;
		return s;
	}
	high = *s;
	high &= 0x3FF;
	if (s[1] < 0xDC00 || s[1] >= 0xE000) {
		// bad surrogate pair
		*rune = badrune;
		s++;
		return s;
	}
	s++;
	low = *s;
	s++;
	low &= 0x3FF;
	*rune = high;
	*rune <<= 10;
	*rune |= low;
	*rune += 0x10000;
	return s;
}