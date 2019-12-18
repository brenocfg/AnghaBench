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
typedef  int /*<<< orphan*/  uint8_t ;
struct al_eth_lm_context {int (* i2c_read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* i2c_write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  retimer_i2c_addr; int /*<<< orphan*/  retimer_bus_id; int /*<<< orphan*/  i2c_context; } ;

/* Variables and functions */
 int EIO ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int al_eth_lm_retimer_ds25_write_reg(struct al_eth_lm_context	*lm_context,
					    uint8_t			reg_addr,
					    uint8_t			reg_mask,
					    uint8_t			reg_value)
{
	uint8_t reg;
	int rc;

	rc = lm_context->i2c_read(lm_context->i2c_context,
				  lm_context->retimer_bus_id,
				  lm_context->retimer_i2c_addr,
				  reg_addr,
				  &reg);

	if (rc != 0)
		return (EIO);

	reg &= ~(reg_mask);
	reg |= reg_value;

	rc = lm_context->i2c_write(lm_context->i2c_context,
				   lm_context->retimer_bus_id,
				   lm_context->retimer_i2c_addr,
				   reg_addr,
				   reg);

	if (rc != 0)
		return (EIO);

	return (0);
}