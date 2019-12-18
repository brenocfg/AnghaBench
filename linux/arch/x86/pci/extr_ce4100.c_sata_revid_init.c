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
struct TYPE_2__ {int value; scalar_t__ mask; } ;
struct sim_dev_reg {TYPE_1__ sim_reg; } ;

/* Variables and functions */

void sata_revid_init(struct sim_dev_reg *reg)
{
	reg->sim_reg.value = 0x01060100;
	reg->sim_reg.mask = 0;
}