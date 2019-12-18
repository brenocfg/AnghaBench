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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;
struct ibv_values_ex {int comp_mask; TYPE_1__ raw_clock; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 int IBV_VALUES_MASK_RAW_CLOCK ; 
 int mlx4_read_clock (struct ibv_context*,int /*<<< orphan*/ *) ; 

int mlx4_query_rt_values(struct ibv_context *context,
			 struct ibv_values_ex *values)
{
	uint32_t comp_mask = 0;
	int err = 0;

	if (values->comp_mask & IBV_VALUES_MASK_RAW_CLOCK) {
		uint64_t cycles;

		err = mlx4_read_clock(context, &cycles);
		if (!err) {
			values->raw_clock.tv_sec = 0;
			values->raw_clock.tv_nsec = cycles;
			comp_mask |= IBV_VALUES_MASK_RAW_CLOCK;
		}
	}

	values->comp_mask = comp_mask;

	return err;
}