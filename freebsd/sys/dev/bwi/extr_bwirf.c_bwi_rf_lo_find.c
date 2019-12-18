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
typedef  int uint16_t ;
struct bwi_tpctl {int tp_ctrl1; int bbp_atten; int rf_atten; } ;
struct bwi_rf_lo {int dummy; } ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAP_MAX ; 
 struct bwi_rf_lo* bwi_get_rf_lo (struct bwi_mac*,int,int) ; 

__attribute__((used)) static __inline struct bwi_rf_lo *
bwi_rf_lo_find(struct bwi_mac *mac, const struct bwi_tpctl *tpctl)
{
	uint16_t rf_atten, bbp_atten;
	int remap_rf_atten;

	remap_rf_atten = 1;
	if (tpctl == NULL) {
		bbp_atten = 2;
		rf_atten = 3;
	} else {
		if (tpctl->tp_ctrl1 == 3)
			remap_rf_atten = 0;

		bbp_atten = tpctl->bbp_atten;
		rf_atten = tpctl->rf_atten;

		if (bbp_atten > 6)
			bbp_atten = 6;
	}

	if (remap_rf_atten) {
#define MAP_MAX	10
		static const uint16_t map[MAP_MAX] =
		{ 11, 10, 11, 12, 13, 12, 13, 12, 13, 12 };

#if 0
		KASSERT(rf_atten < MAP_MAX, ("rf_atten %d", rf_atten));
		rf_atten = map[rf_atten];
#else
		if (rf_atten >= MAP_MAX) {
			rf_atten = 0;	/* XXX */
		} else {
			rf_atten = map[rf_atten];
		}
#endif
#undef MAP_MAX
	}

	return bwi_get_rf_lo(mac, rf_atten, bbp_atten);
}