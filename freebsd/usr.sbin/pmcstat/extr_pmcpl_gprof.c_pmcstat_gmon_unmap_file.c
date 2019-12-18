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
struct pmcstat_gmonfile {int /*<<< orphan*/ * pgf_gmondata; int /*<<< orphan*/  pgf_ndatabytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_SYNC ; 
 int /*<<< orphan*/  msync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmcstat_gmon_unmap_file(struct pmcstat_gmonfile *pgf)
{
	(void) msync(pgf->pgf_gmondata, pgf->pgf_ndatabytes,
	    MS_SYNC);
	(void) munmap(pgf->pgf_gmondata, pgf->pgf_ndatabytes);
	pgf->pgf_gmondata = NULL;
}