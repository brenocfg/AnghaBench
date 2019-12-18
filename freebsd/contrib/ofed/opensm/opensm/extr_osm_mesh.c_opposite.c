#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* node; } ;
typedef  TYPE_2__ switch_t ;
struct TYPE_4__ {int** matrix; unsigned int num_links; int* axes; } ;

/* Variables and functions */

__attribute__((used)) static inline int opposite(switch_t *s, int axis)
{
	unsigned i, j;
	int negaxis = 1 + (1 ^ (axis - 1));

	if (!s->node->matrix)
		return 0;

	for (i = 0; i < s->node->num_links; i++) {
		if (s->node->axes[i] == axis) {
			for (j = 0; j < s->node->num_links; j++) {
				if (j == i)
					continue;
				if (s->node->matrix[i][j] != 2)
					return negaxis;
			}

			return axis;
		}
	}

	return 0;
}