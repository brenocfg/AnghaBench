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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int ether_crc32_be (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
dc_mchash_be(const uint8_t *addr)
{
	uint32_t crc;

	/* Compute CRC for the address value. */
	crc = ether_crc32_be(addr, ETHER_ADDR_LEN);

	/* Return the filter bit position. */
	return ((crc >> 26) & 0x0000003F);
}