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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRC16W ; 
 int** crc16tbl ; 

__attribute__((used)) static uint16_t
lha_crc16(uint16_t crc, const void *pp, size_t len)
{
	const unsigned char *p = (const unsigned char *)pp;
	const uint16_t *buff;
	const union {
		uint32_t i;
		char c[4];
	} u = { 0x01020304 };

	if (len == 0)
		return crc;

	/* Process unaligned address. */
	if (((uintptr_t)p) & (uintptr_t)0x1) {
		crc = (crc >> 8) ^ crc16tbl[0][(crc ^ *p++) & 0xff];
		len--;
	}
	buff = (const uint16_t *)p;
	/*
	 * Modern C compiler such as GCC does not unroll automatically yet
	 * without unrolling pragma, and Clang is so. So we should
	 * unroll this loop for its performance.
	 */
	for (;len >= 8; len -= 8) {
		/* This if statement expects compiler optimization will
		 * remove the statement which will not be executed. */
#undef bswap16
#if defined(_MSC_VER) && _MSC_VER >= 1400  /* Visual Studio */
#  define bswap16(x) _byteswap_ushort(x)
#elif defined(__GNUC__) && ((__GNUC__ == 4 && __GNUC_MINOR__ >= 8) || __GNUC__ > 4)
/* GCC 4.8 and later has __builtin_bswap16() */
#  define bswap16(x) __builtin_bswap16(x)
#elif defined(__clang__)
/* All clang versions have __builtin_bswap16() */
#  define bswap16(x) __builtin_bswap16(x)
#else
#  define bswap16(x) ((((x) >> 8) & 0xff) | ((x) << 8))
#endif
#define CRC16W	do { 	\
		if(u.c[0] == 1) { /* Big endian */		\
			crc ^= bswap16(*buff); buff++;		\
		} else						\
			crc ^= *buff++;				\
		crc = crc16tbl[1][crc & 0xff] ^ crc16tbl[0][crc >> 8];\
} while (0)
		CRC16W;
		CRC16W;
		CRC16W;
		CRC16W;
#undef CRC16W
#undef bswap16
	}

	p = (const unsigned char *)buff;
	for (;len; len--) {
		crc = (crc >> 8) ^ crc16tbl[0][(crc ^ *p++) & 0xff];
	}
	return crc;
}