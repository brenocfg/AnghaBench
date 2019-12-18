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
struct stm_fs {int /*<<< orphan*/  nsdiv; int /*<<< orphan*/  sdiv; int /*<<< orphan*/  pe; int /*<<< orphan*/  mdiv; } ;
struct st_clk_quadfs_fsynth {int /*<<< orphan*/  nsdiv; int /*<<< orphan*/  sdiv; int /*<<< orphan*/  pe; int /*<<< orphan*/  md; } ;

/* Variables and functions */
 int /*<<< orphan*/  quadfs_fsynth_program_enable (struct st_clk_quadfs_fsynth*) ; 
 int /*<<< orphan*/  quadfs_fsynth_program_rate (struct st_clk_quadfs_fsynth*) ; 

__attribute__((used)) static void quadfs_program_and_enable(struct st_clk_quadfs_fsynth *fs,
		struct stm_fs *params)
{
	fs->md = params->mdiv;
	fs->pe = params->pe;
	fs->sdiv = params->sdiv;
	fs->nsdiv = params->nsdiv;

	/*
	 * In some integrations you can only change the fsynth programming when
	 * the parent entity containing it is enabled.
	 */
	quadfs_fsynth_program_rate(fs);
	quadfs_fsynth_program_enable(fs);
}