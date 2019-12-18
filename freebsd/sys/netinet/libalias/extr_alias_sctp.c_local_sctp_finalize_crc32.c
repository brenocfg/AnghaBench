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
local_sctp_finalize_crc32(uint32_t crc32c)
{
	/* This routine is duplicated from SCTP
	 * we need to do that since it MAY be that SCTP
	 * is NOT compiled into the kernel. The CRC32C routines
	 * however are always available in libkern.
	 */
	uint32_t result;
#if BYTE_ORDER == BIG_ENDIAN
	uint8_t byte0, byte1, byte2, byte3;

#endif
	/* Complement the result */
	result = ~crc32c;
#if BYTE_ORDER == BIG_ENDIAN
	/*
	 * For BIG-ENDIAN.. aka Motorola byte order the result is in
	 * little-endian form. So we must manually swap the bytes. Then we
	 * can call htonl() which does nothing...
	 */
	byte0 = result & 0x000000ff;
	byte1 = (result >> 8) & 0x000000ff;
	byte2 = (result >> 16) & 0x000000ff;
	byte3 = (result >> 24) & 0x000000ff;
	crc32c = ((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3);
#else
	/*
	 * For INTEL platforms the result comes out in network order. No
	 * htonl is required or the swap above. So we optimize out both the
	 * htonl and the manual swap above.
	 */
	crc32c = result;
#endif
	return (crc32c);
}