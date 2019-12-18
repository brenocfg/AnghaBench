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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int UNIN_MPIC_OUTPUT_ENABLE ; 
 int UNIN_MPIC_RESET ; 
 int /*<<< orphan*/  UNIN_TOGGLE_REG ; 
 int /*<<< orphan*/  unin_update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unin_enable_mpic(device_t dev)
{
	unin_update_reg(dev, UNIN_TOGGLE_REG, UNIN_MPIC_RESET | UNIN_MPIC_OUTPUT_ENABLE, 0);
}