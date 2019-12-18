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
 scalar_t__ NAE_L4CTABLE0 ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
nlm_setup_l4ctable_even(uint64_t nae_base, int entry, uint32_t im,
    uint32_t l3cm, uint32_t l4pm, uint32_t port,
    uint32_t l3camaddr, uint32_t l4proto)
{
	uint32_t val;

	val = ((im & 0x1) << 19)	|
	    ((l3cm & 0x1) << 18)	|
	    ((l4pm & 0x1) << 17)	|
	    ((port & 0x1f) << 12)	|
	    ((l3camaddr & 0xf) << 8)	|
	    (l4proto & 0xff);
	nlm_write_nae_reg(nae_base, (NAE_L4CTABLE0 + (entry * 2)), val);
}