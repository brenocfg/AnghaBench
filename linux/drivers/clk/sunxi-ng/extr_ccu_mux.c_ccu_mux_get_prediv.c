#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ccu_mux_internal {int shift; int width; int n_predivs; int n_var_predivs; TYPE_2__* var_predivs; TYPE_1__* fixed_predivs; } ;
struct ccu_common {int features; int prediv; scalar_t__ reg; scalar_t__ base; } ;
struct TYPE_4__ {int index; int shift; int width; } ;
struct TYPE_3__ {int index; int div; } ;

/* Variables and functions */
 int CCU_FEATURE_ALL_PREDIV ; 
 int CCU_FEATURE_FIXED_PREDIV ; 
 int CCU_FEATURE_VARIABLE_PREDIV ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static u16 ccu_mux_get_prediv(struct ccu_common *common,
			      struct ccu_mux_internal *cm,
			      int parent_index)
{
	u16 prediv = 1;
	u32 reg;

	if (!((common->features & CCU_FEATURE_FIXED_PREDIV) ||
	      (common->features & CCU_FEATURE_VARIABLE_PREDIV) ||
	      (common->features & CCU_FEATURE_ALL_PREDIV)))
		return 1;

	if (common->features & CCU_FEATURE_ALL_PREDIV)
		return common->prediv;

	reg = readl(common->base + common->reg);
	if (parent_index < 0) {
		parent_index = reg >> cm->shift;
		parent_index &= (1 << cm->width) - 1;
	}

	if (common->features & CCU_FEATURE_FIXED_PREDIV) {
		int i;

		for (i = 0; i < cm->n_predivs; i++)
			if (parent_index == cm->fixed_predivs[i].index)
				prediv = cm->fixed_predivs[i].div;
	}

	if (common->features & CCU_FEATURE_VARIABLE_PREDIV) {
		int i;

		for (i = 0; i < cm->n_var_predivs; i++)
			if (parent_index == cm->var_predivs[i].index) {
				u8 div;

				div = reg >> cm->var_predivs[i].shift;
				div &= (1 << cm->var_predivs[i].width) - 1;
				prediv = div + 1;
			}
	}

	return prediv;
}