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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uc_engine ;

/* Variables and functions */
 int /*<<< orphan*/  uc_reg_write (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uc_trycall (int /*<<< orphan*/ ,char*) ; 

void uc_setreg(uc_engine *uc, int reg_id, uint32_t value) {
    uc_trycall(uc_reg_write(uc, reg_id, &value), "uc_setreg");
}