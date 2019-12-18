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
typedef  int u8 ;
struct clk_omap_reg {int offset; } ;
typedef  unsigned long s16 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* omap3xxx_cm_idlest_offs ; 

__attribute__((used)) static int omap3xxx_cm_split_idlest_reg(struct clk_omap_reg *idlest_reg,
					s16 *prcm_inst,
					u8 *idlest_reg_id)
{
	unsigned long offs;
	u8 idlest_offs;
	int i;

	idlest_offs = idlest_reg->offset & 0xff;
	for (i = 0; i < ARRAY_SIZE(omap3xxx_cm_idlest_offs); i++) {
		if (idlest_offs == omap3xxx_cm_idlest_offs[i]) {
			*idlest_reg_id = i + 1;
			break;
		}
	}

	if (i == ARRAY_SIZE(omap3xxx_cm_idlest_offs))
		return -EINVAL;

	offs = idlest_reg->offset;
	offs &= 0xff00;
	*prcm_inst = offs;

	return 0;
}