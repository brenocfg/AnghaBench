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
struct coh901318_desc {int /*<<< orphan*/  lli; int /*<<< orphan*/  head_ctrl; int /*<<< orphan*/  head_config; } ;
struct coh901318_chan {int busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  coh901318_desc_remove (struct coh901318_desc*) ; 
 int /*<<< orphan*/  coh901318_desc_submit (struct coh901318_chan*,struct coh901318_desc*) ; 
 struct coh901318_desc* coh901318_first_queued (struct coh901318_chan*) ; 
 int /*<<< orphan*/  coh901318_prep_linked_list (struct coh901318_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coh901318_set_conf (struct coh901318_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coh901318_set_ctrl (struct coh901318_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coh901318_start (struct coh901318_chan*) ; 

__attribute__((used)) static struct coh901318_desc *coh901318_queue_start(struct coh901318_chan *cohc)
{
	struct coh901318_desc *cohd;

	/*
	 * start queued jobs, if any
	 * TODO: transmit all queued jobs in one go
	 */
	cohd = coh901318_first_queued(cohc);

	if (cohd != NULL) {
		/* Remove from queue */
		coh901318_desc_remove(cohd);
		/* initiate DMA job */
		cohc->busy = 1;

		coh901318_desc_submit(cohc, cohd);

		/* Program the transaction head */
		coh901318_set_conf(cohc, cohd->head_config);
		coh901318_set_ctrl(cohc, cohd->head_ctrl);
		coh901318_prep_linked_list(cohc, cohd->lli);

		/* start dma job on this channel */
		coh901318_start(cohc);

	}

	return cohd;
}