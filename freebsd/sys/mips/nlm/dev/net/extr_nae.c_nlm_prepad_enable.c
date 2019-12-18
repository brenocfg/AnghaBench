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
 int /*<<< orphan*/  NAE_RX_CONFIG ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_prepad_enable(uint64_t nae_base, int size)
{
	uint32_t val;

	val = nlm_read_nae_reg(nae_base, NAE_RX_CONFIG);
	val |= (1 << 13); /* prepad enable */
	val |= ((size & 0x3) << 22); /* prepad size */
	nlm_write_nae_reg(nae_base, NAE_RX_CONFIG, val);
}