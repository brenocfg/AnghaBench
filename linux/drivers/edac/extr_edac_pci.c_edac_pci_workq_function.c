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
struct work_struct {int dummy; } ;
struct edac_pci_ctl_info {scalar_t__ op_state; int /*<<< orphan*/  work; int /*<<< orphan*/  (* edac_check ) (struct edac_pci_ctl_info*) ;} ;
struct delayed_work {int dummy; } ;

/* Variables and functions */
 scalar_t__ OP_RUNNING_POLL ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 int /*<<< orphan*/  edac_pci_ctls_mutex ; 
 scalar_t__ edac_pci_get_check_errors () ; 
 int edac_pci_get_poll_msec () ; 
 int /*<<< orphan*/  edac_queue_work (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long round_jiffies_relative (unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct edac_pci_ctl_info*) ; 
 struct delayed_work* to_delayed_work (struct work_struct*) ; 
 struct edac_pci_ctl_info* to_edac_pci_ctl_work (struct delayed_work*) ; 

__attribute__((used)) static void edac_pci_workq_function(struct work_struct *work_req)
{
	struct delayed_work *d_work = to_delayed_work(work_req);
	struct edac_pci_ctl_info *pci = to_edac_pci_ctl_work(d_work);
	int msec;
	unsigned long delay;

	edac_dbg(3, "checking\n");

	mutex_lock(&edac_pci_ctls_mutex);

	if (pci->op_state != OP_RUNNING_POLL) {
		mutex_unlock(&edac_pci_ctls_mutex);
		return;
	}

	if (edac_pci_get_check_errors())
		pci->edac_check(pci);

	/* if we are on a one second period, then use round */
	msec = edac_pci_get_poll_msec();
	if (msec == 1000)
		delay = round_jiffies_relative(msecs_to_jiffies(msec));
	else
		delay = msecs_to_jiffies(msec);

	edac_queue_work(&pci->work, delay);

	mutex_unlock(&edac_pci_ctls_mutex);
}