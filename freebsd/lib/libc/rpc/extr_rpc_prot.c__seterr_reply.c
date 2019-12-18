#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_14__ {TYPE_6__ ar_vers; int /*<<< orphan*/  ar_stat; } ;
struct TYPE_10__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_11__ {int /*<<< orphan*/  rj_why; TYPE_3__ rj_vers; int /*<<< orphan*/  rj_stat; } ;
struct TYPE_9__ {int rp_stat; } ;
struct rpc_msg {TYPE_7__ acpted_rply; TYPE_4__ rjcted_rply; TYPE_2__ rm_reply; } ;
struct TYPE_12__ {int /*<<< orphan*/  high; int /*<<< orphan*/  low; } ;
struct TYPE_8__ {int /*<<< orphan*/  s1; } ;
struct rpc_err {int re_status; TYPE_5__ re_vers; int /*<<< orphan*/  re_why; TYPE_1__ re_lb; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
#define  MSG_ACCEPTED 147 
#define  MSG_DENIED 146 
#define  RPC_AUTHERROR 145 
#define  RPC_CANTDECODEARGS 144 
#define  RPC_CANTDECODERES 143 
#define  RPC_CANTENCODEARGS 142 
#define  RPC_CANTRECV 141 
#define  RPC_CANTSEND 140 
#define  RPC_FAILED 139 
#define  RPC_PMAPFAILURE 138 
#define  RPC_PROCUNAVAIL 137 
#define  RPC_PROGNOTREGISTERED 136 
#define  RPC_PROGUNAVAIL 135 
#define  RPC_PROGVERSMISMATCH 134 
#define  RPC_SUCCESS 133 
#define  RPC_SYSTEMERROR 132 
#define  RPC_TIMEDOUT 131 
#define  RPC_UNKNOWNHOST 130 
#define  RPC_UNKNOWNPROTO 129 
#define  RPC_VERSMISMATCH 128 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  accepted (int /*<<< orphan*/ ,struct rpc_err*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rejected (int /*<<< orphan*/ ,struct rpc_err*) ; 

void
_seterr_reply(struct rpc_msg *msg, struct rpc_err *error)
{

	assert(msg != NULL);
	assert(error != NULL);

	/* optimized for normal, SUCCESSful case */
	switch (msg->rm_reply.rp_stat) {

	case MSG_ACCEPTED:
		if (msg->acpted_rply.ar_stat == SUCCESS) {
			error->re_status = RPC_SUCCESS;
			return;
		}
		accepted(msg->acpted_rply.ar_stat, error);
		break;

	case MSG_DENIED:
		rejected(msg->rjcted_rply.rj_stat, error);
		break;

	default:
		error->re_status = RPC_FAILED;
		error->re_lb.s1 = (int32_t)(msg->rm_reply.rp_stat);
		break;
	}
	switch (error->re_status) {

	case RPC_VERSMISMATCH:
		error->re_vers.low = msg->rjcted_rply.rj_vers.low;
		error->re_vers.high = msg->rjcted_rply.rj_vers.high;
		break;

	case RPC_AUTHERROR:
		error->re_why = msg->rjcted_rply.rj_why;
		break;

	case RPC_PROGVERSMISMATCH:
		error->re_vers.low = msg->acpted_rply.ar_vers.low;
		error->re_vers.high = msg->acpted_rply.ar_vers.high;
		break;

	case RPC_FAILED:
	case RPC_SUCCESS:
	case RPC_PROGNOTREGISTERED:
	case RPC_PMAPFAILURE:
	case RPC_UNKNOWNPROTO:
	case RPC_UNKNOWNHOST:
	case RPC_SYSTEMERROR:
	case RPC_CANTDECODEARGS:
	case RPC_PROCUNAVAIL:
	case RPC_PROGUNAVAIL:
	case RPC_TIMEDOUT:
	case RPC_CANTRECV:
	case RPC_CANTSEND:
	case RPC_CANTDECODERES:
	case RPC_CANTENCODEARGS:
	default:
		break;
	}
}