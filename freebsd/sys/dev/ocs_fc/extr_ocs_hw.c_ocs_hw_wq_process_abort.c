#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  io_abort_lock; int /*<<< orphan*/  sli; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_9__ {scalar_t__ saved_len; scalar_t__ saved_ext; scalar_t__ abort_reqtag; scalar_t__ abort_in_progress; int /*<<< orphan*/  rnode; int /*<<< orphan*/  (* abort_done ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,void*) ;void* abort_arg; scalar_t__ status_saved; int /*<<< orphan*/  saved_status; int /*<<< orphan*/  (* done ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,void*) ;void* arg; TYPE_1__* hw; } ;
typedef  TYPE_2__ ocs_hw_io_t ;
typedef  int /*<<< orphan*/  (* ocs_hw_done_t ) (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,void*) ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  hw_wq_callback_t ;

/* Variables and functions */
 scalar_t__ SLI4_FC_LOCAL_REJECT_NO_XRI ; 
 int /*<<< orphan*/  SLI4_FC_WCQE_STATUS_LOCAL_REJECT ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  ocs_hw_assert (int) ; 
 int /*<<< orphan*/  ocs_hw_io_free (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_hw_reqtag_free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ocs_hw_reqtag_get_instance (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sli_fc_ext_status (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_hw_wq_process_abort(void *arg, uint8_t *cqe, int32_t status)
{
	ocs_hw_io_t *io = arg;
	ocs_hw_t *hw = io->hw;
	uint32_t ext = 0;
	uint32_t len = 0;
	hw_wq_callback_t *wqcb;

	/*
	 * For IOs that were aborted internally, we may need to issue the callback here depending
	 * on whether a XRI_ABORTED CQE is expected ot not. If the status is Local Reject/No XRI, then
	 * issue the callback now.
	*/
	ext = sli_fc_ext_status(&hw->sli, cqe);
	if (status == SLI4_FC_WCQE_STATUS_LOCAL_REJECT &&
	    ext == SLI4_FC_LOCAL_REJECT_NO_XRI &&
		io->done != NULL) {
		ocs_hw_done_t  done = io->done;
		void		*arg = io->arg;

		io->done = NULL;

		/*
		 * Use latched status as this is always saved for an internal abort
		 *
		 * Note: We wont have both a done and abort_done function, so don't worry about
		 *       clobbering the len, status and ext fields.
		 */
		status = io->saved_status;
		len = io->saved_len;
		ext = io->saved_ext;
		io->status_saved = 0;
		done(io, io->rnode, len, status, ext, arg);
	}

	if (io->abort_done != NULL) {
		ocs_hw_done_t  done = io->abort_done;
		void		*arg = io->abort_arg;

		io->abort_done = NULL;

		done(io, io->rnode, len, status, ext, arg);
	}
	ocs_lock(&hw->io_abort_lock);
		/* clear abort bit to indicate abort is complete */
		io->abort_in_progress = 0;
	ocs_unlock(&hw->io_abort_lock);

	/* Free the WQ callback */
	ocs_hw_assert(io->abort_reqtag != UINT32_MAX);
	wqcb = ocs_hw_reqtag_get_instance(hw, io->abort_reqtag);
	ocs_hw_reqtag_free(hw, wqcb);

	/*
	 * Call ocs_hw_io_free() because this releases the WQ reservation as
	 * well as doing the refcount put. Don't duplicate the code here.
	 */
	(void)ocs_hw_io_free(hw, io);
}