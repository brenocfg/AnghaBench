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
struct p2p_reg_class {size_t channels; scalar_t__* channel; int /*<<< orphan*/  reg_class; } ;

/* Variables and functions */
 size_t P2P_MAX_REG_CLASS_CHANNELS ; 

__attribute__((used)) static void p2p_reg_class_intersect(const struct p2p_reg_class *a,
				    const struct p2p_reg_class *b,
				    struct p2p_reg_class *res)
{
	size_t i, j;

	res->reg_class = a->reg_class;

	for (i = 0; i < a->channels; i++) {
		for (j = 0; j < b->channels; j++) {
			if (a->channel[i] != b->channel[j])
				continue;
			res->channel[res->channels] = a->channel[i];
			res->channels++;
			if (res->channels == P2P_MAX_REG_CLASS_CHANNELS)
				return;
		}
	}
}