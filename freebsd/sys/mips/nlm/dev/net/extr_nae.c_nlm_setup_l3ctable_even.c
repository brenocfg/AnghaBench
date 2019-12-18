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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ NAE_L3CTABLE0 ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
nlm_setup_l3ctable_even(uint64_t nae_base, int entry, uint32_t l3hdroff,
    uint32_t ipcsum_en, uint32_t l4protooff,
    uint32_t l2proto, uint32_t eth_type)
{
	uint32_t val;

	val = ((l3hdroff & 0x3f) << 26)	|
	    ((l4protooff & 0x3f) << 20)	|
	    ((ipcsum_en & 0x1) << 18)	|
	    ((l2proto & 0x3) << 16)	|
	    (eth_type & 0xffff);
	nlm_write_nae_reg(nae_base, (NAE_L3CTABLE0 + (entry * 2)), val);
}