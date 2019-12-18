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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  xlp_nae_config_lane_gmac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nlm_sgmii_pcs_init(uint64_t nae_base, uint32_t cplx_mask)
{
	xlp_nae_config_lane_gmac(nae_base, cplx_mask);
}