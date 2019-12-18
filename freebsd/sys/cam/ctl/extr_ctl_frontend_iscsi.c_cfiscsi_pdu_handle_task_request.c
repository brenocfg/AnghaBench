#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* task_action; int /*<<< orphan*/  tag_num; int /*<<< orphan*/  tag_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  targ_lun; int /*<<< orphan*/  targ_port; int /*<<< orphan*/  initid; } ;
struct TYPE_11__ {TYPE_4__ nexus; int /*<<< orphan*/  io_type; TYPE_1__* ctl_private; } ;
union ctl_io {TYPE_6__ taskio; TYPE_5__ io_hdr; } ;
struct iscsi_bhs_task_management_response {int bhstmr_flags; int /*<<< orphan*/  bhstmr_initiator_task_tag; int /*<<< orphan*/  bhstmr_response; int /*<<< orphan*/  bhstmr_opcode; } ;
struct iscsi_bhs_task_management_request {int bhstmr_function; int /*<<< orphan*/  bhstmr_initiator_task_tag; int /*<<< orphan*/  bhstmr_referenced_task_tag; int /*<<< orphan*/  bhstmr_lun; } ;
struct icl_pdu {scalar_t__ ip_bhs; } ;
struct cfiscsi_session {int /*<<< orphan*/  cs_outstanding_ctl_pdus; TYPE_3__* cs_target; int /*<<< orphan*/  cs_ctl_initid; } ;
struct TYPE_8__ {int /*<<< orphan*/  targ_port; int /*<<< orphan*/  ctl_pool_ref; } ;
struct TYPE_9__ {TYPE_2__ ct_port; } ;
struct TYPE_7__ {struct icl_pdu* ptr; } ;

/* Variables and functions */
#define  BHSTMR_FUNCTION_ABORT_TASK 137 
#define  BHSTMR_FUNCTION_ABORT_TASK_SET 136 
#define  BHSTMR_FUNCTION_CLEAR_TASK_SET 135 
#define  BHSTMR_FUNCTION_I_T_NEXUS_RESET 134 
#define  BHSTMR_FUNCTION_LOGICAL_UNIT_RESET 133 
#define  BHSTMR_FUNCTION_QUERY_ASYNC_EVENT 132 
#define  BHSTMR_FUNCTION_QUERY_TASK 131 
#define  BHSTMR_FUNCTION_QUERY_TASK_SET 130 
#define  BHSTMR_FUNCTION_TARGET_COLD_RESET 129 
#define  BHSTMR_FUNCTION_TARGET_WARM_RESET 128 
 int /*<<< orphan*/  BHSTMR_RESPONSE_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  CFISCSI_SESSION_DEBUG (struct cfiscsi_session*,char*,...) ; 
 int /*<<< orphan*/  CFISCSI_SESSION_WARN (struct cfiscsi_session*,char*,...) ; 
 int /*<<< orphan*/  CTL_IO_TASK ; 
 size_t CTL_PRIV_FRONTEND ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  CTL_TAG_SIMPLE ; 
 void* CTL_TASK_ABORT_TASK ; 
 void* CTL_TASK_ABORT_TASK_SET ; 
 void* CTL_TASK_CLEAR_TASK_SET ; 
 void* CTL_TASK_I_T_NEXUS_RESET ; 
 void* CTL_TASK_LUN_RESET ; 
 void* CTL_TASK_QUERY_ASYNC_EVENT ; 
 void* CTL_TASK_QUERY_TASK ; 
 void* CTL_TASK_QUERY_TASK_SET ; 
 void* CTL_TASK_TARGET_RESET ; 
 int /*<<< orphan*/  ISCSI_BHS_OPCODE_TASK_RESPONSE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct cfiscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 struct icl_pdu* cfiscsi_pdu_new_response (struct icl_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfiscsi_pdu_queue (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_session_terminate (struct cfiscsi_session*) ; 
 union ctl_io* ctl_alloc_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_decode_lun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_free_io (union ctl_io*) ; 
 int ctl_queue (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_zero_io (union ctl_io*) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfiscsi_pdu_handle_task_request(struct icl_pdu *request)
{
	struct iscsi_bhs_task_management_request *bhstmr;
	struct iscsi_bhs_task_management_response *bhstmr2;
	struct icl_pdu *response;
	struct cfiscsi_session *cs;
	union ctl_io *io;
	int error;

	cs = PDU_SESSION(request);
	bhstmr = (struct iscsi_bhs_task_management_request *)request->ip_bhs;
	io = ctl_alloc_io(cs->cs_target->ct_port.ctl_pool_ref);
	ctl_zero_io(io);
	io->io_hdr.ctl_private[CTL_PRIV_FRONTEND].ptr = request;
	io->io_hdr.io_type = CTL_IO_TASK;
	io->io_hdr.nexus.initid = cs->cs_ctl_initid;
	io->io_hdr.nexus.targ_port = cs->cs_target->ct_port.targ_port;
	io->io_hdr.nexus.targ_lun = ctl_decode_lun(be64toh(bhstmr->bhstmr_lun));
	io->taskio.tag_type = CTL_TAG_SIMPLE; /* XXX */

	switch (bhstmr->bhstmr_function & ~0x80) {
	case BHSTMR_FUNCTION_ABORT_TASK:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_ABORT_TASK");
#endif
		io->taskio.task_action = CTL_TASK_ABORT_TASK;
		io->taskio.tag_num = bhstmr->bhstmr_referenced_task_tag;
		break;
	case BHSTMR_FUNCTION_ABORT_TASK_SET:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_ABORT_TASK_SET");
#endif
		io->taskio.task_action = CTL_TASK_ABORT_TASK_SET;
		break;
	case BHSTMR_FUNCTION_CLEAR_TASK_SET:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_CLEAR_TASK_SET");
#endif
		io->taskio.task_action = CTL_TASK_CLEAR_TASK_SET;
		break;
	case BHSTMR_FUNCTION_LOGICAL_UNIT_RESET:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_LOGICAL_UNIT_RESET");
#endif
		io->taskio.task_action = CTL_TASK_LUN_RESET;
		break;
	case BHSTMR_FUNCTION_TARGET_WARM_RESET:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_TARGET_WARM_RESET");
#endif
		io->taskio.task_action = CTL_TASK_TARGET_RESET;
		break;
	case BHSTMR_FUNCTION_TARGET_COLD_RESET:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_TARGET_COLD_RESET");
#endif
		io->taskio.task_action = CTL_TASK_TARGET_RESET;
		break;
	case BHSTMR_FUNCTION_QUERY_TASK:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_QUERY_TASK");
#endif
		io->taskio.task_action = CTL_TASK_QUERY_TASK;
		io->taskio.tag_num = bhstmr->bhstmr_referenced_task_tag;
		break;
	case BHSTMR_FUNCTION_QUERY_TASK_SET:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_QUERY_TASK_SET");
#endif
		io->taskio.task_action = CTL_TASK_QUERY_TASK_SET;
		break;
	case BHSTMR_FUNCTION_I_T_NEXUS_RESET:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_I_T_NEXUS_RESET");
#endif
		io->taskio.task_action = CTL_TASK_I_T_NEXUS_RESET;
		break;
	case BHSTMR_FUNCTION_QUERY_ASYNC_EVENT:
#if 0
		CFISCSI_SESSION_DEBUG(cs, "BHSTMR_FUNCTION_QUERY_ASYNC_EVENT");
#endif
		io->taskio.task_action = CTL_TASK_QUERY_ASYNC_EVENT;
		break;
	default:
		CFISCSI_SESSION_DEBUG(cs, "unsupported function 0x%x",
		    bhstmr->bhstmr_function & ~0x80);
		ctl_free_io(io);

		response = cfiscsi_pdu_new_response(request, M_NOWAIT);
		if (response == NULL) {
			CFISCSI_SESSION_WARN(cs, "failed to allocate memory; "
			    "dropping connection");
			icl_pdu_free(request);
			cfiscsi_session_terminate(cs);
			return;
		}
		bhstmr2 = (struct iscsi_bhs_task_management_response *)
		    response->ip_bhs;
		bhstmr2->bhstmr_opcode = ISCSI_BHS_OPCODE_TASK_RESPONSE;
		bhstmr2->bhstmr_flags = 0x80;
		bhstmr2->bhstmr_response =
		    BHSTMR_RESPONSE_FUNCTION_NOT_SUPPORTED;
		bhstmr2->bhstmr_initiator_task_tag =
		    bhstmr->bhstmr_initiator_task_tag;
		icl_pdu_free(request);
		cfiscsi_pdu_queue(response);
		return;
	}

	refcount_acquire(&cs->cs_outstanding_ctl_pdus);
	error = ctl_queue(io);
	if (error != CTL_RETVAL_COMPLETE) {
		CFISCSI_SESSION_WARN(cs, "ctl_queue() failed; error %d; "
		    "dropping connection", error);
		ctl_free_io(io);
		refcount_release(&cs->cs_outstanding_ctl_pdus);
		icl_pdu_free(request);
		cfiscsi_session_terminate(cs);
	}
}