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
 int BP_SAIF_CLKMUX ; 
 scalar_t__ CLR ; 
 scalar_t__ DIGCTRL ; 
 int EINVAL ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

int mxs_saif_clkmux_select(unsigned int clkmux)
{
	if (clkmux > 0x3)
		return -EINVAL;

	writel_relaxed(0x3 << BP_SAIF_CLKMUX, DIGCTRL + CLR);
	writel_relaxed(clkmux << BP_SAIF_CLKMUX, DIGCTRL + SET);

	return 0;
}