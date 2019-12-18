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
typedef  char uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int arc4random () ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
nicvf_hw_addr_random(uint8_t *hwaddr)
{
	uint32_t rnd;
	uint8_t addr[ETHER_ADDR_LEN];

	/*
	 * Create randomized MAC address.
	 * Set 'bsd' + random 24 low-order bits.
	 */
	rnd = arc4random() & 0x00ffffff;
	addr[0] = 'b';
	addr[1] = 's';
	addr[2] = 'd';
	addr[3] = rnd >> 16;
	addr[4] = rnd >> 8;
	addr[5] = rnd >> 0;

	memcpy(hwaddr, addr, ETHER_ADDR_LEN);
}