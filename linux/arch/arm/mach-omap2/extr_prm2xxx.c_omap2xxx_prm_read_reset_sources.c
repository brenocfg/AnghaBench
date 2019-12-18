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
typedef  int u32 ;
struct prm_reset_src_map {int reg_shift; int std_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP2_RM_RSTST ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int omap2_prm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct prm_reset_src_map* omap2xxx_prm_reset_src_map ; 

__attribute__((used)) static u32 omap2xxx_prm_read_reset_sources(void)
{
	struct prm_reset_src_map *p;
	u32 r = 0;
	u32 v;

	v = omap2_prm_read_mod_reg(WKUP_MOD, OMAP2_RM_RSTST);

	p = omap2xxx_prm_reset_src_map;
	while (p->reg_shift >= 0 && p->std_shift >= 0) {
		if (v & (1 << p->reg_shift))
			r |= 1 << p->std_shift;
		p++;
	}

	return r;
}