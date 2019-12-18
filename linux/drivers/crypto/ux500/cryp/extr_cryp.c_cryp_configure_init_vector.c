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
struct cryp_init_vector_value {int /*<<< orphan*/  init_value_right; int /*<<< orphan*/  init_value_left; } ;
struct cryp_device_data {TYPE_1__* base; } ;
typedef  enum cryp_init_vector_index { ____Placeholder_cryp_init_vector_index } cryp_init_vector_index ;
struct TYPE_2__ {int /*<<< orphan*/  init_vect_1_r; int /*<<< orphan*/  init_vect_1_l; int /*<<< orphan*/  init_vect_0_r; int /*<<< orphan*/  init_vect_0_l; } ;

/* Variables and functions */
#define  CRYP_INIT_VECTOR_INDEX_0 129 
#define  CRYP_INIT_VECTOR_INDEX_1 128 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ cryp_is_logic_busy (struct cryp_device_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cryp_configure_init_vector(struct cryp_device_data *device_data,
			       enum cryp_init_vector_index
			       init_vector_index,
			       struct cryp_init_vector_value
			       init_vector_value)
{
	while (cryp_is_logic_busy(device_data))
		cpu_relax();

	switch (init_vector_index) {
	case CRYP_INIT_VECTOR_INDEX_0:
		writel_relaxed(init_vector_value.init_value_left,
		       &device_data->base->init_vect_0_l);
		writel_relaxed(init_vector_value.init_value_right,
		       &device_data->base->init_vect_0_r);
		break;
	case CRYP_INIT_VECTOR_INDEX_1:
		writel_relaxed(init_vector_value.init_value_left,
		       &device_data->base->init_vect_1_l);
		writel_relaxed(init_vector_value.init_value_right,
		       &device_data->base->init_vect_1_r);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}