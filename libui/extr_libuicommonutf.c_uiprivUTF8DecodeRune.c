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
typedef  int uint32_t ;

/* Variables and functions */
 int badrune ; 

const char *uiprivUTF8DecodeRune(const char *s, size_t nElem, uint32_t *rune)
{
	uint8_t b, c;
	uint8_t lowestAllowed, highestAllowed;
	size_t i, expected;
	int bad;

	b = (uint8_t) (*s);
	if (b < 0x80) {		// ASCII bytes represent themselves
		*rune = b;
		s++;
		return s;
	}
	// 0xC0 and 0xC1 cover 2-byte overlong equivalents
	// 0xF5 to 0xFD cover values > 0x10FFFF
	// 0xFE and 0xFF were never defined (always illegal)
	if (b < 0xC2 || b > 0xF4) {		// invalid
		*rune = badrune;
		s++;
		return s;
	}

	// this determines the range of allowed first continuation bytes
	lowestAllowed = 0x80;
	highestAllowed = 0xBF;
	switch (b) {
	case 0xE0:
		// disallow 3-byte overlong equivalents
		lowestAllowed = 0xA0;
		break;
	case 0xED:
		// disallow surrogate characters
		highestAllowed = 0x9F;
		break;
	case 0xF0:
		// disallow 4-byte overlong equivalents
		lowestAllowed = 0x90;
		break;
	case 0xF4:
		// disallow values > 0x10FFFF
		highestAllowed = 0x8F;
		break;
	}

	// and this determines how many continuation bytes are expected
	expected = 1;
	if (b >= 0xE0)
		expected++;
	if (b >= 0xF0)
		expected++;
	if (nElem != 0) {				// are there enough bytes?
		nElem--;
		if (nElem < expected) {	// nope
			*rune = badrune;
			s++;
			return s;
		}
	}

	// ensure that everything is correct
	// if not, **only** consume the initial byte
	bad = 0;
	for (i = 0; i < expected; i++) {
		c = (uint8_t) (s[1 + i]);
		if (c < lowestAllowed || c > highestAllowed) {
			bad = 1;
			break;
		}
		// the old lowestAllowed and highestAllowed is only for the first continuation byte
		lowestAllowed = 0x80;
		highestAllowed = 0xBF;
	}
	if (bad) {
		*rune = badrune;
		s++;
		return s;
	}

	// now do the topmost bits
	if (b < 0xE0)
		*rune = b & 0x1F;
	else if (b < 0xF0)
		*rune = b & 0x0F;
	else
		*rune = b & 0x07;
	s++;		// we can finally move on

	// now do the continuation bytes
	for (; expected; expected--) {
		c = (uint8_t) (*s);
		s++;
		c &= 0x3F;		// strip continuation bits
		*rune <<= 6;
		*rune |= c;
	}

	return s;
}