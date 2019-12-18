#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  S; } ;
struct TYPE_31__ {int opcode; int /*<<< orphan*/  itt; int /*<<< orphan*/ * OpcodeSpecificFields; } ;
struct TYPE_25__ {TYPE_6__ data_in; TYPE_7__ bhs; } ;
struct TYPE_26__ {TYPE_1__ ipdu; } ;
struct TYPE_28__ {TYPE_2__ pdu; } ;
typedef  TYPE_4__ pduq_t ;
struct TYPE_27__ {scalar_t__ expCmd; int stat; int /*<<< orphan*/  maxCmd; } ;
struct TYPE_29__ {int /*<<< orphan*/  rsp; TYPE_3__ sn; } ;
typedef  TYPE_5__ isc_session_t ;
typedef  TYPE_6__ data_in_t ;
typedef  TYPE_7__ bhs_t ;
struct TYPE_32__ {scalar_t__ cmd; int expCmd; } ;

/* Variables and functions */
#define  ISCSI_ASYNC 137 
#define  ISCSI_LOGIN_RSP 136 
#define  ISCSI_LOGOUT_RSP 135 
#define  ISCSI_NOP_IN 134 
#define  ISCSI_R2T 133 
#define  ISCSI_READ_DATA 132 
#define  ISCSI_REJECT 131 
#define  ISCSI_SCSI_RSP 130 
#define  ISCSI_TASK_RSP 129 
#define  ISCSI_TEXT_RSP 128 
 int /*<<< orphan*/  _async (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  _nop_in (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  _r2t (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  _read_data (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  _reject (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  _scsi_rsp (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  i_nqueue_rsp (TYPE_5__*,TYPE_4__*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdebug (int,char*,...) ; 
 TYPE_8__* sn ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
ism_recv(isc_session_t *sp, pduq_t *pq)
{
     bhs_t	*bhs;
     int	statSN;

     debug_called(8);

     bhs = &pq->pdu.ipdu.bhs;
     statSN = ntohl(bhs->OpcodeSpecificFields[1]);

#ifdef notyet
     if(sp->sn.expCmd != sn->cmd) {
	  sdebug(1, "we lost something ... exp=0x%x cmd=0x%x",
		 sn->expCmd, sn->cmd);
     }
#endif
     sdebug(5, "opcode=0x%x itt=0x%x stat#0x%x maxcmd=0x%0x",
	    bhs->opcode, ntohl(bhs->itt), statSN, sp->sn.maxCmd);

     switch(bhs->opcode) {
     case ISCSI_READ_DATA: {
	  data_in_t 	*cmd = &pq->pdu.ipdu.data_in;

	  if(cmd->S == 0)
	       break;
     }

     default:
	  if(statSN > (sp->sn.stat + 1)) {
	       sdebug(1, "we lost some rec=0x%x exp=0x%x",
		      statSN, sp->sn.stat);
	       // XXX: must do some error recovery here.
	  }
	  sp->sn.stat = statSN;
     }

     switch(bhs->opcode) {
     case ISCSI_LOGIN_RSP:
     case ISCSI_TEXT_RSP:
     case ISCSI_LOGOUT_RSP:
	  i_nqueue_rsp(sp, pq);
	  wakeup(&sp->rsp);
	  sdebug(3, "wakeup rsp");
	  break;

     case ISCSI_NOP_IN:		_nop_in(sp, pq);	break;
     case ISCSI_SCSI_RSP:	_scsi_rsp(sp, pq);	break;
     case ISCSI_READ_DATA:	_read_data(sp, pq);	break;
     case ISCSI_R2T:		_r2t(sp, pq);		break;
     case ISCSI_REJECT:		_reject(sp, pq);	break;
     case ISCSI_ASYNC:		_async(sp, pq);		break;

     case ISCSI_TASK_RSP:
     default:
	  sdebug(1, "opcode=0x%x itt=0x%x not implemented yet",
		 bhs->opcode, ntohl(bhs->itt));
	  break;
     }
}