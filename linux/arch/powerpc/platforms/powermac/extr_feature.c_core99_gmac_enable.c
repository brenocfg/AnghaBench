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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  UNI_N_CLOCK_CNTL ; 
 int /*<<< orphan*/  UNI_N_CLOCK_CNTL_GMAC ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 int /*<<< orphan*/  UN_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UN_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UN_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static long
core99_gmac_enable(struct device_node *node, long param, long value)
{
	unsigned long flags;

	LOCK(flags);
	if (value)
		UN_BIS(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_GMAC);
	else
		UN_BIC(UNI_N_CLOCK_CNTL, UNI_N_CLOCK_CNTL_GMAC);
	(void)UN_IN(UNI_N_CLOCK_CNTL);
	UNLOCK(flags);
	udelay(20);

	return 0;
}