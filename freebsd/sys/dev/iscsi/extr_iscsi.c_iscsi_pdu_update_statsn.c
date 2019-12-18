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
typedef  scalar_t__ uint32_t ;
struct iscsi_session {scalar_t__ is_statsn; scalar_t__ is_maxcmdsn; scalar_t__ is_expcmdsn; scalar_t__ is_timeout; int /*<<< orphan*/  is_maintenance_cv; int /*<<< orphan*/  is_postponed; } ;
struct iscsi_bhs_data_in {scalar_t__ bhsdi_opcode; int bhsdi_flags; int /*<<< orphan*/  bhsdi_maxcmdsn; int /*<<< orphan*/  bhsdi_expcmdsn; int /*<<< orphan*/  bhsdi_statsn; } ;
struct icl_pdu {scalar_t__ ip_bhs; } ;

/* Variables and functions */
 int BHSDI_FLAGS_S ; 
 scalar_t__ ISCSI_BHS_OPCODE_SCSI_DATA_IN ; 
 int /*<<< orphan*/  ISCSI_SESSION_DEBUG (struct iscsi_session*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_WARN (struct iscsi_session*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ISCSI_SNGT (scalar_t__,scalar_t__) ; 
 scalar_t__ ISCSI_SNLT (scalar_t__,scalar_t__) ; 
 struct iscsi_session* PDU_SESSION (struct icl_pdu const*) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_session_reconnect (struct iscsi_session*) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iscsi_pdu_update_statsn(const struct icl_pdu *response)
{
	const struct iscsi_bhs_data_in *bhsdi;
	struct iscsi_session *is;
	uint32_t expcmdsn, maxcmdsn, statsn;

	is = PDU_SESSION(response);

	ISCSI_SESSION_LOCK_ASSERT(is);

	/*
	 * We're only using fields common for all the response
	 * (target -> initiator) PDUs.
	 */
	bhsdi = (const struct iscsi_bhs_data_in *)response->ip_bhs;
	/*
	 * Ok, I lied.  In case of Data-In, "The fields StatSN, Status,
	 * and Residual Count only have meaningful content if the S bit
	 * is set to 1", so we also need to check the bit specific for
	 * Data-In PDU.
	 */
	if (bhsdi->bhsdi_opcode != ISCSI_BHS_OPCODE_SCSI_DATA_IN ||
	    (bhsdi->bhsdi_flags & BHSDI_FLAGS_S) != 0) {
		statsn = ntohl(bhsdi->bhsdi_statsn);
		if (statsn != is->is_statsn && statsn != (is->is_statsn + 1)) {
			/* XXX: This is normal situation for MCS */
			ISCSI_SESSION_WARN(is, "PDU 0x%x StatSN %u != "
			    "session ExpStatSN %u (or + 1); reconnecting",
			    bhsdi->bhsdi_opcode, statsn, is->is_statsn);
			iscsi_session_reconnect(is);
		}
		if (ISCSI_SNGT(statsn, is->is_statsn))
			is->is_statsn = statsn;
	}

	expcmdsn = ntohl(bhsdi->bhsdi_expcmdsn);
	maxcmdsn = ntohl(bhsdi->bhsdi_maxcmdsn);

	if (ISCSI_SNLT(maxcmdsn + 1, expcmdsn)) {
		ISCSI_SESSION_DEBUG(is,
		    "PDU MaxCmdSN %u + 1 < PDU ExpCmdSN %u; ignoring",
		    maxcmdsn, expcmdsn);
	} else {
		if (ISCSI_SNGT(maxcmdsn, is->is_maxcmdsn)) {
			is->is_maxcmdsn = maxcmdsn;

			/*
			 * Command window increased; kick the maintanance thread
			 * to send out postponed commands.
			 */
			if (!STAILQ_EMPTY(&is->is_postponed))
				cv_signal(&is->is_maintenance_cv);
		} else if (ISCSI_SNLT(maxcmdsn, is->is_maxcmdsn)) {
			/* XXX: This is normal situation for MCS */
			ISCSI_SESSION_DEBUG(is,
			    "PDU MaxCmdSN %u < session MaxCmdSN %u; ignoring",
			    maxcmdsn, is->is_maxcmdsn);
		}

		if (ISCSI_SNGT(expcmdsn, is->is_expcmdsn)) {
			is->is_expcmdsn = expcmdsn;
		} else if (ISCSI_SNLT(expcmdsn, is->is_expcmdsn)) {
			/* XXX: This is normal situation for MCS */
			ISCSI_SESSION_DEBUG(is,
			    "PDU ExpCmdSN %u < session ExpCmdSN %u; ignoring",
			    expcmdsn, is->is_expcmdsn);
		}
	}

	/*
	 * Every incoming PDU - not just NOP-In - resets the ping timer.
	 * The purpose of the timeout is to reset the connection when it stalls;
	 * we don't want this to happen when NOP-In or NOP-Out ends up delayed
	 * in some queue.
	 */
	is->is_timeout = 0;
}