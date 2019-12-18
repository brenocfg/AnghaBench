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
 scalar_t__ NAE_L2_TYPE_PORT0 ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
nlm_setup_l2type(uint64_t nae_base, int hwport, uint32_t l2extlen,
    uint32_t l2extoff, uint32_t extra_hdrsize, uint32_t proto_offset,
    uint32_t fixed_hdroff, uint32_t l2proto)
{
	uint32_t val;

	val = ((l2extlen & 0x3f) << 26)		|
	    ((l2extoff & 0x3f) << 20)		|
	    ((extra_hdrsize & 0x3f) << 14)	|
	    ((proto_offset & 0x3f) << 8)	|
	    ((fixed_hdroff & 0x3f) << 2)	|
	    (l2proto & 0x3);
	nlm_write_nae_reg(nae_base, (NAE_L2_TYPE_PORT0 + hwport), val);
}