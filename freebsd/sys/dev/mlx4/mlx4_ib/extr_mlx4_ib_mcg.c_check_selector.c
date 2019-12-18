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
typedef  int ib_sa_comp_mask ;

/* Variables and functions */
#define  IB_SA_EQ 130 
#define  IB_SA_GT 129 
#define  IB_SA_LT 128 

__attribute__((used)) static int check_selector(ib_sa_comp_mask comp_mask,
			  ib_sa_comp_mask selector_mask,
			  ib_sa_comp_mask value_mask,
			  u8 src_value, u8 dst_value)
{
	int err;
	u8 selector = dst_value >> 6;
	dst_value &= 0x3f;
	src_value &= 0x3f;

	if (!(comp_mask & selector_mask) || !(comp_mask & value_mask))
		return 0;

	switch (selector) {
	case IB_SA_GT:
		err = (src_value <= dst_value);
		break;
	case IB_SA_LT:
		err = (src_value >= dst_value);
		break;
	case IB_SA_EQ:
		err = (src_value != dst_value);
		break;
	default:
		err = 0;
		break;
	}

	return err;
}