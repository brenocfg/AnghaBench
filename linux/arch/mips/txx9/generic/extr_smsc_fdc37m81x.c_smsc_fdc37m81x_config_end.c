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
 int /*<<< orphan*/  SMSC_FDC37M81X_CONFIG_EXIT ; 
 scalar_t__ SMSC_FDC37M81X_CONFIG_INDEX ; 
 scalar_t__ g_smsc_fdc37m81x_base ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

void smsc_fdc37m81x_config_end(void)
{
	if (g_smsc_fdc37m81x_base)
		outb(SMSC_FDC37M81X_CONFIG_EXIT,
		     g_smsc_fdc37m81x_base + SMSC_FDC37M81X_CONFIG_INDEX);
}