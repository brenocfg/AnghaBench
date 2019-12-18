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

__attribute__((used)) static uint32_t
sctp_finalize_crc32c(uint32_t crc32c)
{
	uint32_t result;
#if BYTE_ORDER == BIG_ENDIAN
	uint8_t byte0, byte1, byte2, byte3;
#endif

	/* Complement the result */
	result = ~crc32c;
#if BYTE_ORDER == BIG_ENDIAN
	/*
	 * For BIG-ENDIAN platforms the result is in little-endian form. So
	 * we must swap the bytes to return the result in network byte
	 * order.
	 */
	byte0 = result & 0x000000ff;
	byte1 = (result >> 8) & 0x000000ff;
	byte2 = (result >> 16) & 0x000000ff;
	byte3 = (result >> 24) & 0x000000ff;
	crc32c = ((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3);
#else
	/*
	 * For LITTLE ENDIAN platforms the result is in already in network
	 * byte order.
	 */
	crc32c = result;
#endif
	return (crc32c);
}