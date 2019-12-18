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
typedef  size_t u8 ;
typedef  int u64 ;
struct amd64_pvt {int fam; scalar_t__ ext_model; int model; TYPE_1__* csels; } ;
struct TYPE_2__ {int* csbases; int* csmasks; } ;

/* Variables and functions */
 int GENMASK_ULL (int,int) ; 
 scalar_t__ K8_REV_F ; 

__attribute__((used)) static void get_cs_base_and_mask(struct amd64_pvt *pvt, int csrow, u8 dct,
				 u64 *base, u64 *mask)
{
	u64 csbase, csmask, base_bits, mask_bits;
	u8 addr_shift;

	if (pvt->fam == 0xf && pvt->ext_model < K8_REV_F) {
		csbase		= pvt->csels[dct].csbases[csrow];
		csmask		= pvt->csels[dct].csmasks[csrow];
		base_bits	= GENMASK_ULL(31, 21) | GENMASK_ULL(15, 9);
		mask_bits	= GENMASK_ULL(29, 21) | GENMASK_ULL(15, 9);
		addr_shift	= 4;

	/*
	 * F16h and F15h, models 30h and later need two addr_shift values:
	 * 8 for high and 6 for low (cf. F16h BKDG).
	 */
	} else if (pvt->fam == 0x16 ||
		  (pvt->fam == 0x15 && pvt->model >= 0x30)) {
		csbase          = pvt->csels[dct].csbases[csrow];
		csmask          = pvt->csels[dct].csmasks[csrow >> 1];

		*base  = (csbase & GENMASK_ULL(15,  5)) << 6;
		*base |= (csbase & GENMASK_ULL(30, 19)) << 8;

		*mask = ~0ULL;
		/* poke holes for the csmask */
		*mask &= ~((GENMASK_ULL(15, 5)  << 6) |
			   (GENMASK_ULL(30, 19) << 8));

		*mask |= (csmask & GENMASK_ULL(15, 5))  << 6;
		*mask |= (csmask & GENMASK_ULL(30, 19)) << 8;

		return;
	} else {
		csbase		= pvt->csels[dct].csbases[csrow];
		csmask		= pvt->csels[dct].csmasks[csrow >> 1];
		addr_shift	= 8;

		if (pvt->fam == 0x15)
			base_bits = mask_bits =
				GENMASK_ULL(30,19) | GENMASK_ULL(13,5);
		else
			base_bits = mask_bits =
				GENMASK_ULL(28,19) | GENMASK_ULL(13,5);
	}

	*base  = (csbase & base_bits) << addr_shift;

	*mask  = ~0ULL;
	/* poke holes for the csmask */
	*mask &= ~(mask_bits << addr_shift);
	/* OR them in */
	*mask |= (csmask & mask_bits) << addr_shift;
}