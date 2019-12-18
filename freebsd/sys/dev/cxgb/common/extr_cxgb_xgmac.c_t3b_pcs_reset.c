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
struct cmac {scalar_t__ offset; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 scalar_t__ A_XGM_RESET_CTRL ; 
 int /*<<< orphan*/  F_PCS_RESET_ ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t3b_pcs_reset(struct cmac *mac)
{
	t3_set_reg_field(mac->adapter, A_XGM_RESET_CTRL + mac->offset,
			 F_PCS_RESET_, 0);

	/* No delay required */

	t3_set_reg_field(mac->adapter, A_XGM_RESET_CTRL + mac->offset, 0,
			 F_PCS_RESET_);
}