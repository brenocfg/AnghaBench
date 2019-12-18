#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_clk_quadfs_fsynth {size_t chan; scalar_t__ lock; int /*<<< orphan*/  nsdiv; TYPE_1__* data; int /*<<< orphan*/  sdiv; int /*<<< orphan*/  pe; int /*<<< orphan*/  md; } ;
struct TYPE_2__ {scalar_t__ nsdiv_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKGEN_WRITE (struct st_clk_quadfs_fsynth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * en ; 
 int /*<<< orphan*/ * mdiv ; 
 int /*<<< orphan*/ * nsdiv ; 
 int /*<<< orphan*/ * pe ; 
 int /*<<< orphan*/ * sdiv ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 

__attribute__((used)) static void quadfs_fsynth_program_rate(struct st_clk_quadfs_fsynth *fs)
{
	unsigned long flags = 0;

	/*
	 * Ensure the md/pe parameters are ignored while we are
	 * reprogramming them so we can get a glitchless change
	 * when fine tuning the speed of a running clock.
	 */
	CLKGEN_WRITE(fs, en[fs->chan], 0);

	CLKGEN_WRITE(fs, mdiv[fs->chan], fs->md);
	CLKGEN_WRITE(fs, pe[fs->chan], fs->pe);
	CLKGEN_WRITE(fs, sdiv[fs->chan], fs->sdiv);

	if (fs->lock)
		spin_lock_irqsave(fs->lock, flags);

	if (fs->data->nsdiv_present)
		CLKGEN_WRITE(fs, nsdiv[fs->chan], fs->nsdiv);

	if (fs->lock)
		spin_unlock_irqrestore(fs->lock, flags);
}