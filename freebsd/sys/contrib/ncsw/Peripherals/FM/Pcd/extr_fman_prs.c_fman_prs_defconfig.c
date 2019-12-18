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
struct fman_prs_cfg {int prs_exceptions; int /*<<< orphan*/  max_prs_cyc_lim; scalar_t__ port_id_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MAX_PRS_CYC_LIM ; 

void fman_prs_defconfig(struct fman_prs_cfg *cfg)
{
	cfg->port_id_stat = 0;
	cfg->max_prs_cyc_lim = DEFAULT_MAX_PRS_CYC_LIM;
	cfg->prs_exceptions = 0x03000000;
}