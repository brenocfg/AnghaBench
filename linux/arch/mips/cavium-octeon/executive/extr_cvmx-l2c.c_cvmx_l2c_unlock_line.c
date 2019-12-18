#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int addr; int L; scalar_t__ V; } ;
union cvmx_l2c_tag {TYPE_1__ s; } ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ADD_SEG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CVMX_CACHE_WBIL2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CVMX_L2C_TAG_ADDR_ALIAS_SHIFT ; 
 int CVMX_L2_ASSOC ; 
 int /*<<< orphan*/  CVMX_MIPS_SPACE_XKPHYS ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_l2c_address_to_index (int) ; 
 int /*<<< orphan*/  cvmx_l2c_flush_line (int,int) ; 
 union cvmx_l2c_tag cvmx_l2c_get_tag (int,int) ; 

int cvmx_l2c_unlock_line(uint64_t address)
{

	if (OCTEON_IS_MODEL(OCTEON_CN63XX)) {
		int assoc;
		union cvmx_l2c_tag tag;
		uint32_t tag_addr;
		uint32_t index = cvmx_l2c_address_to_index(address);

		tag_addr = ((address >> CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) & ((1 << CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) - 1));

		/*
		 * For 63XX, we can flush a line by using the physical
		 * address directly, so finding the cache line used by
		 * the address is only required to provide the proper
		 * return value for the function.
		 */
		for (assoc = 0; assoc < CVMX_L2_ASSOC; assoc++) {
			tag = cvmx_l2c_get_tag(assoc, index);

			if (tag.s.V && (tag.s.addr == tag_addr)) {
				CVMX_CACHE_WBIL2(CVMX_ADD_SEG(CVMX_MIPS_SPACE_XKPHYS, address), 0);
				return tag.s.L;
			}
		}
	} else {
		int assoc;
		union cvmx_l2c_tag tag;
		uint32_t tag_addr;

		uint32_t index = cvmx_l2c_address_to_index(address);

		/* Compute portion of address that is stored in tag */
		tag_addr = ((address >> CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) & ((1 << CVMX_L2C_TAG_ADDR_ALIAS_SHIFT) - 1));
		for (assoc = 0; assoc < CVMX_L2_ASSOC; assoc++) {
			tag = cvmx_l2c_get_tag(assoc, index);

			if (tag.s.V && (tag.s.addr == tag_addr)) {
				cvmx_l2c_flush_line(assoc, index);
				return tag.s.L;
			}
		}
	}
	return 0;
}