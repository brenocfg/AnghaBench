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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  bswap16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 

void
cd9660_bothendian_word(uint16_t dw, unsigned char *fourchar)
{
	uint16_t le, be;
#if BYTE_ORDER == LITTLE_ENDIAN
	le = dw;
	be = bswap16(dw);
#endif
#if BYTE_ORDER == BIG_ENDIAN
	be = dw;
	le = bswap16(dw);
#endif
	memcpy(fourchar, &le, 2);
	memcpy((fourchar+2), &be, 2);
}