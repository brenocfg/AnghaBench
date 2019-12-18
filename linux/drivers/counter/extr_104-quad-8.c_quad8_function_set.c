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
struct quad8_iio {unsigned int* quadrature_mode; unsigned int* quadrature_scale; int* count_mode; unsigned int* synchronous_mode; int* index_polarity; int base; } ;
struct counter_device {struct quad8_iio* priv; } ;
struct counter_count {int id; } ;

/* Variables and functions */
 unsigned int QUAD8_CMR_QUADRATURE_X1 ; 
 unsigned int QUAD8_CMR_QUADRATURE_X2 ; 
 unsigned int QUAD8_CMR_QUADRATURE_X4 ; 
 size_t QUAD8_COUNT_FUNCTION_PULSE_DIRECTION ; 
#define  QUAD8_COUNT_FUNCTION_QUADRATURE_X1 130 
#define  QUAD8_COUNT_FUNCTION_QUADRATURE_X2 129 
#define  QUAD8_COUNT_FUNCTION_QUADRATURE_X4 128 
 unsigned int QUAD8_CTR_CMR ; 
 unsigned int const QUAD8_CTR_IDR ; 
 int /*<<< orphan*/  outb (unsigned int const,int const) ; 

__attribute__((used)) static int quad8_function_set(struct counter_device *counter,
	struct counter_count *count, size_t function)
{
	struct quad8_iio *const priv = counter->priv;
	const int id = count->id;
	unsigned int *const quadrature_mode = priv->quadrature_mode + id;
	unsigned int *const scale = priv->quadrature_scale + id;
	unsigned int mode_cfg = priv->count_mode[id] << 1;
	unsigned int *const synchronous_mode = priv->synchronous_mode + id;
	const unsigned int idr_cfg = priv->index_polarity[id] << 1;
	const int base_offset = priv->base + 2 * id + 1;

	if (function == QUAD8_COUNT_FUNCTION_PULSE_DIRECTION) {
		*quadrature_mode = 0;

		/* Quadrature scaling only available in quadrature mode */
		*scale = 0;

		/* Synchronous function not supported in non-quadrature mode */
		if (*synchronous_mode) {
			*synchronous_mode = 0;
			/* Disable synchronous function mode */
			outb(QUAD8_CTR_IDR | idr_cfg, base_offset);
		}
	} else {
		*quadrature_mode = 1;

		switch (function) {
		case QUAD8_COUNT_FUNCTION_QUADRATURE_X1:
			*scale = 0;
			mode_cfg |= QUAD8_CMR_QUADRATURE_X1;
			break;
		case QUAD8_COUNT_FUNCTION_QUADRATURE_X2:
			*scale = 1;
			mode_cfg |= QUAD8_CMR_QUADRATURE_X2;
			break;
		case QUAD8_COUNT_FUNCTION_QUADRATURE_X4:
			*scale = 2;
			mode_cfg |= QUAD8_CMR_QUADRATURE_X4;
			break;
		}
	}

	/* Load mode configuration to Counter Mode Register */
	outb(QUAD8_CTR_CMR | mode_cfg, base_offset);

	return 0;
}