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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  build_byte_cache (int**) ; 

__attribute__((used)) static uint32_t
sym_hash_fn(uint32_t sip, uint32_t dip, uint16_t sp, uint32_t dp)
{
	uint32_t rc = 0;
	static int first_time = 1;
	static uint32_t byte_cache[256][4];
	uint8_t *sip_b = (uint8_t *)&sip,
		*dip_b = (uint8_t *)&dip,
		*sp_b  = (uint8_t *)&sp,
		*dp_b  = (uint8_t *)&dp;

	if (first_time) {
		build_byte_cache(byte_cache);
		first_time = 0;
	}

	rc = byte_cache[sip_b[3]][0] ^
	     byte_cache[sip_b[2]][1] ^
	     byte_cache[sip_b[1]][2] ^
	     byte_cache[sip_b[0]][3] ^
	     byte_cache[dip_b[3]][0] ^
	     byte_cache[dip_b[2]][1] ^
	     byte_cache[dip_b[1]][2] ^
	     byte_cache[dip_b[0]][3] ^
	     byte_cache[sp_b[1]][0] ^
	     byte_cache[sp_b[0]][1] ^
	     byte_cache[dp_b[1]][2] ^
	     byte_cache[dp_b[0]][3];

	return rc;
}