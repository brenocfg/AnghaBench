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
struct printer {int /*<<< orphan*/  mode_set; int /*<<< orphan*/  trailer; int /*<<< orphan*/  status_file; int /*<<< orphan*/  stat_send; int /*<<< orphan*/  stat_recv; int /*<<< orphan*/  spool_dir; int /*<<< orphan*/  remote_queue; int /*<<< orphan*/  remote_host; int /*<<< orphan*/  restrict_grp; int /*<<< orphan*/  lp; int /*<<< orphan*/  lock_file; int /*<<< orphan*/  log_file; int /*<<< orphan*/  form_feed; int /*<<< orphan*/ * filters; int /*<<< orphan*/  acct_file; int /*<<< orphan*/  printer; } ;
typedef  enum lpd_filters { ____Placeholder_lpd_filters } lpd_filters ;

/* Variables and functions */
 int LPF_COUNT ; 
 int /*<<< orphan*/  cfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_printer (struct printer*) ; 

void
free_printer(struct printer *pp)
{
	enum lpd_filters filt;
#define	cfree(x)	do { if (x) free(x); } while(0)
	cfree(pp->printer);
	cfree(pp->acct_file);
	for (filt = 0; filt < LPF_COUNT; filt++)
		cfree(pp->filters[filt]);
	cfree(pp->form_feed);
	cfree(pp->log_file);
	cfree(pp->lock_file);
	cfree(pp->lp);
	cfree(pp->restrict_grp);
	cfree(pp->remote_host);
	cfree(pp->remote_queue);
	cfree(pp->spool_dir);
	cfree(pp->stat_recv);
	cfree(pp->stat_send);
	cfree(pp->status_file);
	cfree(pp->trailer);
	cfree(pp->mode_set);

	init_printer(pp);
}