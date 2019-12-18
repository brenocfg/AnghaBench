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
 int /*<<< orphan*/  CMD_IDU_SET_DEST ; 
 int /*<<< orphan*/  __mcip_cmd_data (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void idu_set_dest(unsigned int cmn_irq, unsigned int cpu_mask)
{
	__mcip_cmd_data(CMD_IDU_SET_DEST, cmn_irq, cpu_mask);
}