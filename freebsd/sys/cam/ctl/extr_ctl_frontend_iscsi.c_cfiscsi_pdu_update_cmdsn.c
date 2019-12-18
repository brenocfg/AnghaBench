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
typedef  scalar_t__ uint32_t ;
struct iscsi_bhs_scsi_command {int /*<<< orphan*/  bhssc_expstatsn; int /*<<< orphan*/  bhssc_cmdsn; } ;
struct icl_pdu {TYPE_1__* ip_bhs; } ;
struct cfiscsi_session {scalar_t__ cs_statsn; int cs_cmdsn; scalar_t__ cs_timeout; } ;
struct TYPE_2__ {int bhs_opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_SESSION_DEBUG (struct cfiscsi_session*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_LOCK (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_UNLOCK (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_WARN (struct cfiscsi_session*,char*,scalar_t__,int) ; 
 int ISCSI_BHS_OPCODE_IMMEDIATE ; 
 int ISCSI_BHS_OPCODE_SCSI_DATA_OUT ; 
 scalar_t__ ISCSI_SNGT (scalar_t__,int) ; 
 scalar_t__ ISCSI_SNLT (scalar_t__,int) ; 
 struct cfiscsi_session* PDU_SESSION (struct icl_pdu const*) ; 
 int /*<<< orphan*/  cfiscsi_session_terminate (struct cfiscsi_session*) ; 
 int maxtags ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cfiscsi_pdu_update_cmdsn(const struct icl_pdu *request)
{
	const struct iscsi_bhs_scsi_command *bhssc;
	struct cfiscsi_session *cs;
	uint32_t cmdsn, expstatsn;

	cs = PDU_SESSION(request);

	/*
	 * Every incoming PDU - not just NOP-Out - resets the ping timer.
	 * The purpose of the timeout is to reset the connection when it stalls;
	 * we don't want this to happen when NOP-In or NOP-Out ends up delayed
	 * in some queue.
	 *
	 * XXX: Locking?
	 */
	cs->cs_timeout = 0;

	/*
	 * Data-Out PDUs don't contain CmdSN.
	 */
	if ((request->ip_bhs->bhs_opcode & ~ISCSI_BHS_OPCODE_IMMEDIATE) ==
	    ISCSI_BHS_OPCODE_SCSI_DATA_OUT)
		return (false);

	/*
	 * We're only using fields common for all the request
	 * (initiator -> target) PDUs.
	 */
	bhssc = (const struct iscsi_bhs_scsi_command *)request->ip_bhs;
	cmdsn = ntohl(bhssc->bhssc_cmdsn);
	expstatsn = ntohl(bhssc->bhssc_expstatsn);

	CFISCSI_SESSION_LOCK(cs);
#if 0
	if (expstatsn != cs->cs_statsn) {
		CFISCSI_SESSION_DEBUG(cs, "received PDU with ExpStatSN %d, "
		    "while current StatSN is %d", expstatsn,
		    cs->cs_statsn);
	}
#endif

	if ((request->ip_bhs->bhs_opcode & ISCSI_BHS_OPCODE_IMMEDIATE) == 0) {
		/*
		 * The target MUST silently ignore any non-immediate command
		 * outside of this range.
		 */
		if (ISCSI_SNLT(cmdsn, cs->cs_cmdsn) ||
		    ISCSI_SNGT(cmdsn, cs->cs_cmdsn - 1 + maxtags)) {
			CFISCSI_SESSION_UNLOCK(cs);
			CFISCSI_SESSION_WARN(cs, "received PDU with CmdSN %u, "
			    "while expected %u", cmdsn, cs->cs_cmdsn);
			return (true);
		}

		/*
		 * We don't support multiple connections now, so any
		 * discontinuity in CmdSN means lost PDUs.  Since we don't
		 * support PDU retransmission -- terminate the connection.
		 */
		if (cmdsn != cs->cs_cmdsn) {
			CFISCSI_SESSION_UNLOCK(cs);
			CFISCSI_SESSION_WARN(cs, "received PDU with CmdSN %u, "
			    "while expected %u; dropping connection",
			    cmdsn, cs->cs_cmdsn);
			cfiscsi_session_terminate(cs);
			return (true);
		}
		cs->cs_cmdsn++;
	}

	CFISCSI_SESSION_UNLOCK(cs);

	return (false);
}