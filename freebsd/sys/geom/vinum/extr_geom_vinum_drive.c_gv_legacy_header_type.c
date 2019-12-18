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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int GV_LEGACY_AMD64 ; 
 int GV_LEGACY_I386 ; 
 int GV_LEGACY_POWERPC ; 
 int GV_LEGACY_SPARC64 ; 

__attribute__((used)) static int
gv_legacy_header_type(uint8_t *hdr, int bigendian)
{
	uint32_t *i32;
	int arch_32, arch_64, i;

	/* Set arch according to endianness. */
	if (bigendian) {
		arch_32 = GV_LEGACY_POWERPC;
		arch_64 = GV_LEGACY_SPARC64;
	} else {
		arch_32 = GV_LEGACY_I386;
		arch_64 = GV_LEGACY_AMD64;
	}

	/* if non-empty hostname overlaps 64-bit config_length */
	i32 = (uint32_t *)(hdr + 12);
	if (*i32 != 0)
		return (arch_32);
	/* check for non-empty hostname */
	if (hdr[16] != 0)
		return (arch_64);
	/* check bytes past 32-bit structure */
	for (i = 100; i < 120; i++)
		if (hdr[i] != 0)
			return (arch_32);
	/* check for overlapping timestamp */
	i32 = (uint32_t *)(hdr + 84);

	if (*i32 == 0)
		return (arch_64);
	return (arch_32);
}