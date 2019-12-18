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
struct cryp_key_value {int /*<<< orphan*/  key_value_right; int /*<<< orphan*/  key_value_left; } ;
struct cryp_device_data {TYPE_1__* base; } ;
typedef  enum cryp_key_reg_index { ____Placeholder_cryp_key_reg_index } cryp_key_reg_index ;
struct TYPE_2__ {int /*<<< orphan*/  key_4_r; int /*<<< orphan*/  key_4_l; int /*<<< orphan*/  key_3_r; int /*<<< orphan*/  key_3_l; int /*<<< orphan*/  key_2_r; int /*<<< orphan*/  key_2_l; int /*<<< orphan*/  key_1_r; int /*<<< orphan*/  key_1_l; } ;

/* Variables and functions */
#define  CRYP_KEY_REG_1 131 
#define  CRYP_KEY_REG_2 130 
#define  CRYP_KEY_REG_3 129 
#define  CRYP_KEY_REG_4 128 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ cryp_is_logic_busy (struct cryp_device_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cryp_configure_key_values(struct cryp_device_data *device_data,
			      enum cryp_key_reg_index key_reg_index,
			      struct cryp_key_value key_value)
{
	while (cryp_is_logic_busy(device_data))
		cpu_relax();

	switch (key_reg_index) {
	case CRYP_KEY_REG_1:
		writel_relaxed(key_value.key_value_left,
				&device_data->base->key_1_l);
		writel_relaxed(key_value.key_value_right,
				&device_data->base->key_1_r);
		break;
	case CRYP_KEY_REG_2:
		writel_relaxed(key_value.key_value_left,
				&device_data->base->key_2_l);
		writel_relaxed(key_value.key_value_right,
				&device_data->base->key_2_r);
		break;
	case CRYP_KEY_REG_3:
		writel_relaxed(key_value.key_value_left,
				&device_data->base->key_3_l);
		writel_relaxed(key_value.key_value_right,
				&device_data->base->key_3_r);
		break;
	case CRYP_KEY_REG_4:
		writel_relaxed(key_value.key_value_left,
				&device_data->base->key_4_l);
		writel_relaxed(key_value.key_value_right,
				&device_data->base->key_4_r);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}