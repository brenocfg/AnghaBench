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
struct dc_softc {int dc_flags; } ;

/* Variables and functions */
 int DC_128BIT_HASH ; 
 int DC_64BIT_HASH ; 
 int DC_BITS_128 ; 
 int DC_BITS_512 ; 
 int DC_BITS_64 ; 
 scalar_t__ DC_IS_XIRCOM (struct dc_softc*) ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int ether_crc32_le (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
dc_mchash_le(struct dc_softc *sc, const uint8_t *addr)
{
	uint32_t crc;

	/* Compute CRC for the address value. */
	crc = ether_crc32_le(addr, ETHER_ADDR_LEN);

	/*
	 * The hash table on the PNIC II and the MX98715AEC-C/D/E
	 * chips is only 128 bits wide.
	 */
	if (sc->dc_flags & DC_128BIT_HASH)
		return (crc & ((1 << DC_BITS_128) - 1));

	/* The hash table on the MX98715BEC is only 64 bits wide. */
	if (sc->dc_flags & DC_64BIT_HASH)
		return (crc & ((1 << DC_BITS_64) - 1));

	/* Xircom's hash filtering table is different (read: weird) */
	/* Xircom uses the LEAST significant bits */
	if (DC_IS_XIRCOM(sc)) {
		if ((crc & 0x180) == 0x180)
			return ((crc & 0x0F) + (crc & 0x70) * 3 + (14 << 4));
		else
			return ((crc & 0x1F) + ((crc >> 1) & 0xF0) * 3 +
			    (12 << 4));
	}

	return (crc & ((1 << DC_BITS_512) - 1));
}