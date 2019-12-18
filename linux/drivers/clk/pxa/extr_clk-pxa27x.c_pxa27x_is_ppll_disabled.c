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
 int CCCR_PPDIS_BIT ; 
 int /*<<< orphan*/  CCSR ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 

bool pxa27x_is_ppll_disabled(void)
{
	unsigned long ccsr = readl(CCSR);

	return ccsr & (1 << CCCR_PPDIS_BIT);
}