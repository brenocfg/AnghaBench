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
 int /*<<< orphan*/  IMCR_CCFG ; 
 unsigned int imcr_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imcr_set (int /*<<< orphan*/ ,unsigned int) ; 

void L2_cache_set_mode(unsigned int mode)
{
	unsigned int ccfg = imcr_get(IMCR_CCFG);

	/* Clear and set the L2MODE bits in CCFG */
	ccfg &= ~7;
	ccfg |= (mode & 7);
	imcr_set(IMCR_CCFG, ccfg);
	ccfg = imcr_get(IMCR_CCFG);
}