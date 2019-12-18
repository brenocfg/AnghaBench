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
typedef  int uint32_t ;
struct bge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_SRAM_MAC_ADDR_HIGH_MB ; 
 int /*<<< orphan*/  BGE_SRAM_MAC_ADDR_LOW_MB ; 
 int bge_readmem_ind (struct bge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_get_eaddr_mem(struct bge_softc *sc, uint8_t ether_addr[])
{
	uint32_t mac_addr;

	mac_addr = bge_readmem_ind(sc, BGE_SRAM_MAC_ADDR_HIGH_MB);
	if ((mac_addr >> 16) == 0x484b) {
		ether_addr[0] = (uint8_t)(mac_addr >> 8);
		ether_addr[1] = (uint8_t)mac_addr;
		mac_addr = bge_readmem_ind(sc, BGE_SRAM_MAC_ADDR_LOW_MB);
		ether_addr[2] = (uint8_t)(mac_addr >> 24);
		ether_addr[3] = (uint8_t)(mac_addr >> 16);
		ether_addr[4] = (uint8_t)(mac_addr >> 8);
		ether_addr[5] = (uint8_t)mac_addr;
		return (0);
	}
	return (1);
}