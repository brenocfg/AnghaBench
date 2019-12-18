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
 int /*<<< orphan*/  pnv_default_stop_mask ; 
 int /*<<< orphan*/  pnv_default_stop_val ; 
 int /*<<< orphan*/  power9_idle_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void power9_idle(void)
{
	power9_idle_type(pnv_default_stop_val, pnv_default_stop_mask);
}