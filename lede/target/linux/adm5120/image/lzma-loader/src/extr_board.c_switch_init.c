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

/* Variables and functions */
 int CPUP_CONF_DCPUP ; 
 int PORT_CONF0_DP_SHIFT ; 
 int SWITCH_PORTS_HW ; 
 int /*<<< orphan*/  SWITCH_REG_CPUP_CONF ; 
 int /*<<< orphan*/  SWITCH_REG_GPIO_CONF0 ; 
 int /*<<< orphan*/  SWITCH_REG_GPIO_CONF2 ; 
 int /*<<< orphan*/  SWITCH_REG_PORT0_LED ; 
 int /*<<< orphan*/  SWITCH_REG_PORT1_LED ; 
 int /*<<< orphan*/  SWITCH_REG_PORT2_LED ; 
 int /*<<< orphan*/  SWITCH_REG_PORT3_LED ; 
 int /*<<< orphan*/  SWITCH_REG_PORT4_LED ; 
 int /*<<< orphan*/  SWITCH_REG_PORT_CONF0 ; 
 int /*<<< orphan*/  SWITCH_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void switch_init(void)
{
	/* disable PHYS ports */
	SWITCH_WRITE(SWITCH_REG_PORT_CONF0,
	    (SWITCH_PORTS_HW << PORT_CONF0_DP_SHIFT));

	/* disable CPU port */
	SWITCH_WRITE(SWITCH_REG_CPUP_CONF, CPUP_CONF_DCPUP);

	/* disable GPIO lines */
	SWITCH_WRITE(SWITCH_REG_GPIO_CONF0, 0);
	SWITCH_WRITE(SWITCH_REG_GPIO_CONF2, 0);

	/* disable LED lines */
	SWITCH_WRITE(SWITCH_REG_PORT0_LED, 0);
	SWITCH_WRITE(SWITCH_REG_PORT1_LED, 0);
	SWITCH_WRITE(SWITCH_REG_PORT2_LED, 0);
	SWITCH_WRITE(SWITCH_REG_PORT3_LED, 0);
	SWITCH_WRITE(SWITCH_REG_PORT4_LED, 0);
}