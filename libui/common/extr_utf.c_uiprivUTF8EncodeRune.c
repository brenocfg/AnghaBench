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

size_t uiprivUTF8EncodeRune(uint32_t rune, char *encoded)
{
	uint8_t b, c, d, e;
	size_t n;

	// not in the valid range for Unicode
	if (rune > 0x10FFFF)
		rune = badrune;
	// surrogate runes cannot be encoded
	if (rune >= 0xD800 && rune < 0xE000)
		rune = badrune;

	if (rune < 0x80) {		// ASCII bytes represent themselves
		b = (uint8_t) (rune & 0xFF);
		n = 1;
		goto done;
	}
	if (rune < 0x800) {		// two-byte encoding
		c = (uint8_t) (rune & 0x3F);
		c |= 0x80;
		rune >>= 6;
		b = (uint8_t) (rune & 0x1F);
		b |= 0xC0;
		n = 2;
		goto done;
	}
	if (rune < 0x10000) {	// three-byte encoding
		d = (uint8_t) (rune & 0x3F);
		d |= 0x80;
		rune >>= 6;
		c = (uint8_t) (rune & 0x3F);
		c |= 0x80;
		rune >>= 6;
		b = (uint8_t) (rune & 0x0F);
		b |= 0xE0;
		n = 3;
		goto done;
	}
	// otherwise use a four-byte encoding
	e = (uint8_t) (rune & 0x3F);
	e |= 0x80;
	rune >>= 6;
	d = (uint8_t) (rune & 0x3F);
	d |= 0x80;
	rune >>= 6;
	c = (uint8_t) (rune & 0x3F);
	c |= 0x80;
	rune >>= 6;
	b = (uint8_t) (rune & 0x07);
	b |= 0xF0;
	n = 4;

done:
	encoded[0] = b;
	if (n > 1)
		encoded[1] = c;
	if (n > 2)
		encoded[2] = d;
	if (n > 3)
		encoded[3] = e;
	return n;
}