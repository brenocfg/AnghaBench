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
struct p2p_reg_class {scalar_t__ reg_class; } ;
struct p2p_channels {size_t reg_classes; struct p2p_reg_class* reg_class; } ;

/* Variables and functions */
 size_t P2P_MAX_REG_CLASSES ; 
 int /*<<< orphan*/  os_memcpy (struct p2p_reg_class*,struct p2p_reg_class const*,int) ; 
 int /*<<< orphan*/  p2p_op_class_union (struct p2p_reg_class*,struct p2p_reg_class const*) ; 

void p2p_channels_union_inplace(struct p2p_channels *res,
				const struct p2p_channels *b)
{
	size_t i, j;

	for (i = 0; i < res->reg_classes; i++) {
		struct p2p_reg_class *cl = &res->reg_class[i];
		for (j = 0; j < b->reg_classes; j++) {
			const struct p2p_reg_class *b_cl = &b->reg_class[j];
			if (cl->reg_class != b_cl->reg_class)
				continue;
			p2p_op_class_union(cl, b_cl);
		}
	}

	for (j = 0; j < b->reg_classes; j++) {
		const struct p2p_reg_class *b_cl = &b->reg_class[j];

		for (i = 0; i < res->reg_classes; i++) {
			struct p2p_reg_class *cl = &res->reg_class[i];
			if (cl->reg_class == b_cl->reg_class)
				break;
		}

		if (i == res->reg_classes) {
			if (res->reg_classes == P2P_MAX_REG_CLASSES)
				return;
			os_memcpy(&res->reg_class[res->reg_classes++],
				  b_cl, sizeof(struct p2p_reg_class));
		}
	}
}