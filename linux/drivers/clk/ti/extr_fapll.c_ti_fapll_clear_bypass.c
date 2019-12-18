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
typedef  int /*<<< orphan*/  u32 ;
struct fapll_data {int /*<<< orphan*/  base; scalar_t__ bypass_bit_inverted; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAPLL_MAIN_BP ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_fapll_clear_bypass(struct fapll_data *fd)
{
	u32 v = readl_relaxed(fd->base);

	if (fd->bypass_bit_inverted)
		v |= FAPLL_MAIN_BP;
	else
		v &= ~FAPLL_MAIN_BP;
	writel_relaxed(v, fd->base);
}