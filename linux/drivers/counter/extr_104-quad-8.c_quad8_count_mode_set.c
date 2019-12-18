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
struct quad8_iio {int base; size_t* count_mode; int* quadrature_scale; scalar_t__* quadrature_mode; } ;
struct counter_device {struct quad8_iio* priv; } ;
struct counter_count {int id; } ;

/* Variables and functions */
#define  COUNTER_COUNT_MODE_MODULO_N 131 
#define  COUNTER_COUNT_MODE_NON_RECYCLE 130 
#define  COUNTER_COUNT_MODE_NORMAL 129 
#define  COUNTER_COUNT_MODE_RANGE_LIMIT 128 
 unsigned int QUAD8_CTR_CMR ; 
 int /*<<< orphan*/  outb (unsigned int,int const) ; 

__attribute__((used)) static int quad8_count_mode_set(struct counter_device *counter,
	struct counter_count *count, size_t cnt_mode)
{
	struct quad8_iio *const priv = counter->priv;
	unsigned int mode_cfg;
	const int base_offset = priv->base + 2 * count->id + 1;

	/* Map Generic Counter count mode to 104-QUAD-8 count mode */
	switch (cnt_mode) {
	case COUNTER_COUNT_MODE_NORMAL:
		cnt_mode = 0;
		break;
	case COUNTER_COUNT_MODE_RANGE_LIMIT:
		cnt_mode = 1;
		break;
	case COUNTER_COUNT_MODE_NON_RECYCLE:
		cnt_mode = 2;
		break;
	case COUNTER_COUNT_MODE_MODULO_N:
		cnt_mode = 3;
		break;
	}

	priv->count_mode[count->id] = cnt_mode;

	/* Set count mode configuration value */
	mode_cfg = cnt_mode << 1;

	/* Add quadrature mode configuration */
	if (priv->quadrature_mode[count->id])
		mode_cfg |= (priv->quadrature_scale[count->id] + 1) << 3;

	/* Load mode configuration to Counter Mode Register */
	outb(QUAD8_CTR_CMR | mode_cfg, base_offset);

	return 0;
}