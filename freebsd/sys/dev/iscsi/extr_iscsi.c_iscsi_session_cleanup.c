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
struct iscsi_session {int is_simq_frozen; int /*<<< orphan*/ * is_devq; int /*<<< orphan*/ * is_sim; int /*<<< orphan*/ * is_path; int /*<<< orphan*/  is_postponed; } ;
struct icl_pdu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_DEV_NOT_THERE ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  ISCSI_SESSION_DEBUG (struct iscsi_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT (struct iscsi_session*) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct icl_pdu* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 
 int /*<<< orphan*/  ip_next ; 
 int /*<<< orphan*/  iscsi_session_terminate_tasks (struct iscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
iscsi_session_cleanup(struct iscsi_session *is, bool destroy_sim)
{
	struct icl_pdu *pdu;

	ISCSI_SESSION_LOCK_ASSERT(is);

	/*
	 * Don't queue any new PDUs.
	 */
	if (is->is_sim != NULL && is->is_simq_frozen == false) {
		ISCSI_SESSION_DEBUG(is, "freezing");
		xpt_freeze_simq(is->is_sim, 1);
		is->is_simq_frozen = true;
	}

	/*
	 * Remove postponed PDUs.
	 */
	if (!STAILQ_EMPTY(&is->is_postponed))
		xpt_release_simq(is->is_sim, 1);
	while ((pdu = STAILQ_FIRST(&is->is_postponed)) != NULL) {
		STAILQ_REMOVE_HEAD(&is->is_postponed, ip_next);
		icl_pdu_free(pdu);
	}

	if (destroy_sim == false) {
		/*
		 * Terminate SCSI tasks, asking CAM to requeue them.
		 */
		iscsi_session_terminate_tasks(is, CAM_REQUEUE_REQ);
		return;
	}

	iscsi_session_terminate_tasks(is, CAM_DEV_NOT_THERE);

	if (is->is_sim == NULL)
		return;

	ISCSI_SESSION_DEBUG(is, "deregistering SIM");
	xpt_async(AC_LOST_DEVICE, is->is_path, NULL);

	if (is->is_simq_frozen) {
		xpt_release_simq(is->is_sim, 1);
		is->is_simq_frozen = false;
	}

	xpt_free_path(is->is_path);
	is->is_path = NULL;
	xpt_bus_deregister(cam_sim_path(is->is_sim));
	cam_sim_free(is->is_sim, TRUE /*free_devq*/);
	is->is_sim = NULL;
	is->is_devq = NULL;
}