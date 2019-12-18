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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  bswap32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 

void
cd9660_bothendian_dword(uint32_t dw, unsigned char *eightchar)
{
	uint32_t le, be;
#if BYTE_ORDER == LITTLE_ENDIAN
	le = dw;
	be = bswap32(dw);
#endif
#if BYTE_ORDER == BIG_ENDIAN
	be = dw;
	le = bswap32(dw);
#endif
	memcpy(eightchar, &le, 4);
	memcpy((eightchar+4), &be, 4);
}