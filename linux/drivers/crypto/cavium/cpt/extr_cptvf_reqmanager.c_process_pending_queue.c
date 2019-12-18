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
struct TYPE_2__ {unsigned char compcode; } ;
union cpt_res_s {TYPE_1__ s; } ;
struct pending_queue {size_t front; int /*<<< orphan*/  lock; int /*<<< orphan*/  pending_count; struct pending_entry* head; } ;
struct pending_qinfo {struct pending_queue* queue; } ;
struct pending_entry {int busy; int /*<<< orphan*/  callback_arg; int /*<<< orphan*/  (* callback ) (unsigned char,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * post_arg; int /*<<< orphan*/ * completion_addr; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {struct pci_dev* pdev; } ;
struct cpt_info_buffer {unsigned char* alternate_caddr; scalar_t__ extra_time; int /*<<< orphan*/  cptvf; scalar_t__ time_in; } ;

/* Variables and functions */
 unsigned char COMPLETION_CODE_INIT ; 
 int CPT_COMMAND_TIMEOUT ; 
 unsigned char CPT_COMP_E_FAULT ; 
 unsigned char CPT_COMP_E_SWERR ; 
 int HZ ; 
 scalar_t__ TIME_IN_RESET_COUNT ; 
 int /*<<< orphan*/  atomic64_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  do_post_process (int /*<<< orphan*/ ,struct cpt_info_buffer*) ; 
 int /*<<< orphan*/  do_request_cleanup (struct cpt_vf*,struct cpt_info_buffer*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pending_queue_inc_front (struct pending_qinfo*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void process_pending_queue(struct cpt_vf *cptvf,
					 struct pending_qinfo *pqinfo,
					 int qno)
{
	struct pci_dev *pdev = cptvf->pdev;
	struct pending_queue *pqueue = &pqinfo->queue[qno];
	struct pending_entry *pentry = NULL;
	struct cpt_info_buffer *info = NULL;
	union cpt_res_s *status = NULL;
	unsigned char ccode;

	while (1) {
		spin_lock_bh(&pqueue->lock);
		pentry = &pqueue->head[pqueue->front];
		if (unlikely(!pentry->busy)) {
			spin_unlock_bh(&pqueue->lock);
			break;
		}

		info = (struct cpt_info_buffer *)pentry->post_arg;
		if (unlikely(!info)) {
			dev_err(&pdev->dev, "Pending Entry post arg NULL\n");
			pending_queue_inc_front(pqinfo, qno);
			spin_unlock_bh(&pqueue->lock);
			continue;
		}

		status = (union cpt_res_s *)pentry->completion_addr;
		ccode = status->s.compcode;
		if ((status->s.compcode == CPT_COMP_E_FAULT) ||
		    (status->s.compcode == CPT_COMP_E_SWERR)) {
			dev_err(&pdev->dev, "Request failed with %s\n",
				(status->s.compcode == CPT_COMP_E_FAULT) ?
				"DMA Fault" : "Software error");
			pentry->completion_addr = NULL;
			pentry->busy = false;
			atomic64_dec((&pqueue->pending_count));
			pentry->post_arg = NULL;
			pending_queue_inc_front(pqinfo, qno);
			do_request_cleanup(cptvf, info);
			spin_unlock_bh(&pqueue->lock);
			break;
		} else if (status->s.compcode == COMPLETION_CODE_INIT) {
			/* check for timeout */
			if (time_after_eq(jiffies,
					  (info->time_in +
					  (CPT_COMMAND_TIMEOUT * HZ)))) {
				dev_err(&pdev->dev, "Request timed out");
				pentry->completion_addr = NULL;
				pentry->busy = false;
				atomic64_dec((&pqueue->pending_count));
				pentry->post_arg = NULL;
				pending_queue_inc_front(pqinfo, qno);
				do_request_cleanup(cptvf, info);
				spin_unlock_bh(&pqueue->lock);
				break;
			} else if ((*info->alternate_caddr ==
				(~COMPLETION_CODE_INIT)) &&
				(info->extra_time < TIME_IN_RESET_COUNT)) {
				info->time_in = jiffies;
				info->extra_time++;
				spin_unlock_bh(&pqueue->lock);
				break;
			}
		}

		pentry->completion_addr = NULL;
		pentry->busy = false;
		pentry->post_arg = NULL;
		atomic64_dec((&pqueue->pending_count));
		pending_queue_inc_front(pqinfo, qno);
		spin_unlock_bh(&pqueue->lock);

		do_post_process(info->cptvf, info);
		/*
		 * Calling callback after we find
		 * that the request has been serviced
		 */
		pentry->callback(ccode, pentry->callback_arg);
	}
}