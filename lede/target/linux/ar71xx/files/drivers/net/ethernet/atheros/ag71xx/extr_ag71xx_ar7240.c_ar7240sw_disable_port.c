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
struct ar7240sw {int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7240_PORT_CTRL_STATE_DISABLED ; 
 int /*<<< orphan*/  AR7240_REG_PORT_CTRL (unsigned int) ; 
 int /*<<< orphan*/  ar7240sw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar7240sw_disable_port(struct ar7240sw *as, unsigned port)
{
	ar7240sw_reg_write(as->mii_bus, AR7240_REG_PORT_CTRL(port),
			   AR7240_PORT_CTRL_STATE_DISABLED);
}