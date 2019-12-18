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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_CONTROL ; 
 int /*<<< orphan*/  F_GLOBALENABLE ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
t3_sge_start(adapter_t *sc)
{
	t3_set_reg_field(sc, A_SG_CONTROL, F_GLOBALENABLE, F_GLOBALENABLE);
}