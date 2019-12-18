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
 int /*<<< orphan*/  NAE_VFBID_DESTMAP_CMD ; 
 int nlm_get_vfbid_mapping (int) ; 
 int /*<<< orphan*/  nlm_write_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_setup_vfbid_mapping(uint64_t nae_base)
{
	uint32_t val;
	int dest_vc, vfbid;

	/* 127 is max vfbid */
	for (vfbid = 127; vfbid >= 0; vfbid--) {
		dest_vc = nlm_get_vfbid_mapping(vfbid);
		if (dest_vc < 0)
			continue;
		val = (dest_vc << 16) | (vfbid << 4) | 1;
		nlm_write_nae_reg(nae_base, NAE_VFBID_DESTMAP_CMD, val);
	}
}