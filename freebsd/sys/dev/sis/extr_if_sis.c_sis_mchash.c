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
struct sis_softc {scalar_t__ sis_type; scalar_t__ sis_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ SIS_REV_635 ; 
 scalar_t__ SIS_REV_900B ; 
 scalar_t__ SIS_TYPE_83815 ; 
 int ether_crc32_be (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
sis_mchash(struct sis_softc *sc, const uint8_t *addr)
{
	uint32_t		crc;

	/* Compute CRC for the address value. */
	crc = ether_crc32_be(addr, ETHER_ADDR_LEN);

	/*
	 * return the filter bit position
	 *
	 * The NatSemi chip has a 512-bit filter, which is
	 * different than the SiS, so we special-case it.
	 */
	if (sc->sis_type == SIS_TYPE_83815)
		return (crc >> 23);
	else if (sc->sis_rev >= SIS_REV_635 ||
	    sc->sis_rev == SIS_REV_900B)
		return (crc >> 24);
	else
		return (crc >> 25);
}