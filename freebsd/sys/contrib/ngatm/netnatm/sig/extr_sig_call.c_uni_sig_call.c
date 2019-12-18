#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct uni_msg {int dummy; } ;
struct TYPE_24__ {int /*<<< orphan*/  cause; int /*<<< orphan*/  epref; } ;
struct TYPE_23__ {int /*<<< orphan*/  cause; int /*<<< orphan*/  epref; } ;
struct TYPE_22__ {int /*<<< orphan*/  epref; } ;
struct TYPE_21__ {int /*<<< orphan*/  epref; } ;
struct TYPE_20__ {int /*<<< orphan*/  epref; } ;
struct TYPE_19__ {int /*<<< orphan*/  epref; } ;
struct TYPE_18__ {int /*<<< orphan*/  epref; } ;
struct TYPE_17__ {int /*<<< orphan*/  epref; } ;
struct TYPE_16__ {int /*<<< orphan*/  epref; } ;
struct TYPE_13__ {TYPE_9__ drop_party_ack; TYPE_8__ drop_party; TYPE_7__ add_party_rej; TYPE_6__ party_alerting; TYPE_5__ add_party; TYPE_4__ connect; TYPE_3__ alerting; TYPE_2__ call_proc; TYPE_1__ setup; } ;
struct uni_all {TYPE_10__ u; } ;
struct uni {int /*<<< orphan*/  arg; TYPE_11__* funcs; int /*<<< orphan*/  cause; int /*<<< orphan*/  proto; int /*<<< orphan*/  cx; int /*<<< orphan*/  sb_tb; } ;
struct call {size_t cstate; struct uni* uni; int /*<<< orphan*/  type; scalar_t__ mine; int /*<<< orphan*/  cref; } ;
typedef  enum call_sig { ____Placeholder_call_sig } call_sig ;
struct TYPE_15__ {int name; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* uni_output ) (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*) ;} ;

/* Variables and functions */
#define  CALLST_N1 202 
#define  CALLST_N10 201 
#define  CALLST_N11 200 
#define  CALLST_N12 199 
#define  CALLST_N3 198 
#define  CALLST_N4 197 
#define  CALLST_N6 196 
#define  CALLST_N7 195 
#define  CALLST_N8 194 
#define  CALLST_N9 193 
#define  CALLST_NULL 192 
#define  CALLST_U1 191 
#define  CALLST_U10 190 
#define  CALLST_U11 189 
#define  CALLST_U12 188 
#define  CALLST_U3 187 
#define  CALLST_U4 186 
#define  CALLST_U6 185 
#define  CALLST_U7 184 
#define  CALLST_U8 183 
#define  CALLST_U9 182 
 int /*<<< orphan*/  CALL_FREE (struct call*) ; 
 int /*<<< orphan*/  CALL_LEAF ; 
 int /*<<< orphan*/  CALL_ROOT ; 
#define  SIGC_ABORT_CALL_request 181 
#define  SIGC_ADD_PARTY 180 
#define  SIGC_ADD_PARTY_ACK 179 
#define  SIGC_ADD_PARTY_ACK_request 178 
#define  SIGC_ADD_PARTY_REJ 177 
#define  SIGC_ADD_PARTY_REJ_indication 176 
#define  SIGC_ADD_PARTY_REJ_request 175 
#define  SIGC_ADD_PARTY_request 174 
#define  SIGC_ALERTING 173 
#define  SIGC_ALERTING_request 172 
#define  SIGC_CALL_DELETE 171 
#define  SIGC_CALL_PROC 170 
#define  SIGC_COBISETUP 169 
#define  SIGC_CONNECT 168 
#define  SIGC_CONNECT_ACK 167 
#define  SIGC_DROP_PARTY 166 
#define  SIGC_DROP_PARTY_ACK 165 
#define  SIGC_DROP_PARTY_ACK_indication 164 
#define  SIGC_DROP_PARTY_ACK_request 163 
#define  SIGC_DROP_PARTY_indication 162 
#define  SIGC_DROP_PARTY_request 161 
#define  SIGC_END 160 
#define  SIGC_LINK_ESTABLISH_ERROR_indication 159 
#define  SIGC_LINK_ESTABLISH_confirm 158 
#define  SIGC_LINK_ESTABLISH_indication 157 
#define  SIGC_LINK_RELEASE_indication 156 
#define  SIGC_NOTIFY 155 
#define  SIGC_NOTIFY_request 154 
#define  SIGC_PARTY_ALERTING 153 
#define  SIGC_PARTY_ALERTING_request 152 
#define  SIGC_PARTY_DESTROYED 151 
#define  SIGC_PROCEEDING_request 150 
#define  SIGC_RELEASE 149 
#define  SIGC_RELEASE_COMPL 148 
#define  SIGC_RELEASE_request 147 
#define  SIGC_RELEASE_response 146 
#define  SIGC_SEND_ADD_PARTY_REJ 145 
#define  SIGC_SEND_DROP_PARTY 144 
#define  SIGC_SEND_DROP_PARTY_ACK 143 
#define  SIGC_SEND_STATUS_ENQ 142 
#define  SIGC_SETUP 141 
#define  SIGC_SETUP_COMPLETE_request 140 
#define  SIGC_SETUP_request 139 
#define  SIGC_SETUP_response 138 
#define  SIGC_STATUS 137 
#define  SIGC_STATUS_ENQ 136 
#define  SIGC_STATUS_ENQUIRY_request 135 
#define  SIGC_T301 134 
#define  SIGC_T303 133 
#define  SIGC_T308 132 
#define  SIGC_T310 131 
#define  SIGC_T313 130 
#define  SIGC_T322 129 
#define  SIGC_UNKNOWN 128 
 int /*<<< orphan*/  UNIAPI_ERROR_BAD_CALLSTATE ; 
 int /*<<< orphan*/  UNIAPI_OK ; 
 int /*<<< orphan*/  UNIAPI_PARTY_DESTROYED ; 
 int /*<<< orphan*/  UNIPROTO_UNI40N ; 
 int /*<<< orphan*/  UNIPROTO_UNI40U ; 
 int /*<<< orphan*/  UNI_CALLSTATE_U0 ; 
 int /*<<< orphan*/  UNI_CAUSE_MSG_INCOMP ; 
 int UNI_EPSTATE_NULL ; 
 int /*<<< orphan*/  UNI_FAC_CALL ; 
 int /*<<< orphan*/  UNI_FAC_ERR ; 
 int /*<<< orphan*/  UNI_FREE (struct uni_all*) ; 
 int /*<<< orphan*/  VERBOSE (struct uni*,int /*<<< orphan*/ ,int,char*,int,...) ; 
 int /*<<< orphan*/ * call_sigs ; 
 TYPE_12__* callstates ; 
 int /*<<< orphan*/  clear_callD (struct call*) ; 
 int /*<<< orphan*/  n10_connect_ack (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  n8_setup_compl_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nx_add_party_rej_indication (struct call*,struct uni_msg*) ; 
 int /*<<< orphan*/  nx_drop_party_ack_indication (struct call*,struct uni_msg*) ; 
 int /*<<< orphan*/  nx_drop_party_indication (struct call*,struct uni_msg*) ; 
 int /*<<< orphan*/  stub1 (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*) ; 
 int /*<<< orphan*/  u11n12_release (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  u11n12_t308 (struct call*) ; 
 int /*<<< orphan*/  u1n6_call_proc (struct call*,struct uni_msg*,struct uni_all*,int const) ; 
 int /*<<< orphan*/  u1n6_t303 (struct call*) ; 
 int /*<<< orphan*/  u3n9_t310 (struct call*) ; 
 int /*<<< orphan*/  u4n7_t301 (struct call*) ; 
 int /*<<< orphan*/  u6n1_proceeding_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  u8_connect_ack (struct call*,struct uni_msg*,struct uni_all*,int) ; 
 int /*<<< orphan*/  u8_t313 (struct call*) ; 
 int /*<<< orphan*/  un0_setup (struct call*,struct uni_msg*,struct uni_all*,int const) ; 
 int /*<<< orphan*/  un0_setup_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  un10_add_party_ack_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  un10_link_establish_confirm (struct call*) ; 
 int /*<<< orphan*/  un10_link_establish_error_indication (struct call*) ; 
 int /*<<< orphan*/  un10_link_establish_indication (struct call*) ; 
 int /*<<< orphan*/  un10_link_release_indication (struct call*) ; 
 int /*<<< orphan*/  un10n8_add_party_ack (struct call*,struct uni_msg*,struct uni_all*,int) ; 
 int /*<<< orphan*/  un11un12_status (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  uni_bad_message (struct call*,struct uni_all*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uni_decode_body (struct uni_msg*,struct uni_all*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uni_destroy_call (struct call*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 
 int /*<<< orphan*/  uni_party_act_count (struct call*,int) ; 
 int /*<<< orphan*/  uni_send_output (struct uni_all*,struct uni*) ; 
 int /*<<< orphan*/  uniapi_call_error (struct call*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniapi_uni_error (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_add_party (struct call*,struct uni_msg*,struct uni_all*,int) ; 
 int /*<<< orphan*/  unx_add_party_rej (struct call*,struct uni_msg*,struct uni_all*,int) ; 
 int /*<<< orphan*/  unx_add_party_rej_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_add_party_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_alerting (struct call*,struct uni_msg*,struct uni_all*,int const) ; 
 int /*<<< orphan*/  unx_alerting_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  unx_connect (struct call*,struct uni_msg*,struct uni_all*,int const) ; 
 int /*<<< orphan*/  unx_drop_party (struct call*,struct uni_msg*,struct uni_all*,int) ; 
 int /*<<< orphan*/  unx_drop_party_ack (struct call*,struct uni_msg*,struct uni_all*,int) ; 
 int /*<<< orphan*/  unx_drop_party_ack_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_drop_party_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_link_establish_indication (struct call*) ; 
 int /*<<< orphan*/  unx_link_release_indication (struct call*) ; 
 int /*<<< orphan*/  unx_notify (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  unx_notify_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_party_alerting (struct call*,struct uni_msg*,struct uni_all*,int) ; 
 int /*<<< orphan*/  unx_party_alerting_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_release (struct call*,struct uni_msg*,struct uni_all*,int const) ; 
 int /*<<< orphan*/  unx_release_compl (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  unx_release_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  unx_release_response (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_send_add_party_rej (struct call*,struct uni_all*) ; 
 int /*<<< orphan*/  unx_send_party_status_enq (struct call*,struct uni_all*) ; 
 int /*<<< orphan*/  unx_setup_response (struct call*,struct uni_msg*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  unx_status (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  unx_status_enq (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  unx_status_enquiry_request (struct call*,struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unx_t322 (struct call*) ; 
 int /*<<< orphan*/  unx_unknown (struct call*,struct uni_msg*,struct uni_all*) ; 
 int /*<<< orphan*/  ux_add_party_rej_indication (struct call*,struct uni_msg*) ; 
 int /*<<< orphan*/  ux_drop_party_ack_indication (struct call*,struct uni_msg*) ; 
 int /*<<< orphan*/  ux_drop_party_indication (struct call*,struct uni_msg*) ; 

void
uni_sig_call(struct call *c, enum call_sig sig, uint32_t cookie,
    struct uni_msg *msg, struct uni_all *u)
{
	if (sig >= SIGC_END) {
		VERBOSE(c->uni, UNI_FAC_ERR, 1,
		    "Signal %d outside of range to Call-Control", sig);
		if (msg)
			uni_msg_destroy(msg);
		if (u)
			UNI_FREE(u);
		return;
	}

	VERBOSE(c->uni, UNI_FAC_CALL, 1, "Signal %s in state %s of call %u/%s"
	    "; cookie %u", call_sigs[sig], callstates[c->cstate].name, c->cref,
	    c->mine ? "mine" : "his", cookie);

	switch (sig) {

	  case SIGC_LINK_RELEASE_indication:
		if (c->cstate == CALLST_U10 || c->cstate == CALLST_N10)
			/* Q.2971:Call-Control-U 36/39 */
			/* Q.2971:Call-Control-N 20/39 */
			un10_link_release_indication(c);
		else
			/* Q.2971:Call-Control-U 36/39 */
			/* Q.2971:Call-Control-N 37/39 */
			unx_link_release_indication(c);
		break;

	  case SIGC_LINK_ESTABLISH_ERROR_indication:
		if (c->cstate != CALLST_U10 && c->cstate != CALLST_N10) {
			VERBOSE(c->uni, UNI_FAC_ERR, 1,
			    "link-establish-error.indication in cs=%s",
			    callstates[c->cstate].name);
			break;
		}
		/* Q.2971:Call-Control-U 19/39 */
		/* Q.2971:Call-Control-N 20/39 */
		un10_link_establish_error_indication(c);
		break;

	  case SIGC_LINK_ESTABLISH_indication:
		switch (c->cstate) {

		  case CALLST_U1: case CALLST_N1:
		  case CALLST_U3: case CALLST_N3:
		  case CALLST_U4: case CALLST_N4:
		  case CALLST_U6: case CALLST_N6:
		  case CALLST_U7: case CALLST_N7:
		  case CALLST_U8: case CALLST_N8:
		  case CALLST_U9: case CALLST_N9:
			/* Q.2971:Call-Control-U 36/39 */
			/* Q.2971:Call-Control-N 37/39 */
			unx_link_establish_indication(c);
			break;

		  case CALLST_U10: case CALLST_N10:
			/* Q.2971:Call-Control-U 19/39 */
			/* Q.2971:Call-Control-N 20/39 */
			un10_link_establish_indication(c);
			break;

		  case CALLST_U11: case CALLST_N11:
		  case CALLST_U12: case CALLST_N12:
			/* Q.2971:Call-Control-U 36/39 */
			/* Q.2971:Call-Control-N 37/39 */
			break;

		  default:
			VERBOSE(c->uni, UNI_FAC_ERR, 1,
			    "link-establish.indication in cs=%s",
			    callstates[c->cstate].name);
		}
		break;

	  case SIGC_LINK_ESTABLISH_confirm:
		if (c->cstate != CALLST_U10 && c->cstate != CALLST_N10) {
			VERBOSE(c->uni, UNI_FAC_ERR, 1,
			    "link-establish.confirm in cs=%s",
			    callstates[c->cstate].name);
			break;
		}
		/* Q.2971:Call-Control-U 19/39 */
		/* Q.2971:Call-Control-N 20/39 */
		un10_link_establish_confirm(c);
		break;

	  case SIGC_UNKNOWN:
		/* Q.2971:Call-Control 35/39 */
		/* Q.2971:Call-Control 36/39 */
		unx_unknown(c, msg, u);
		break;

	  case SIGC_SETUP:
		if (c->cstate != CALLST_NULL) {
			(void)uni_decode_body(msg, u, &c->uni->cx);
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.setup.epref, -1);
			goto drop;
		}
		if (c->uni->proto == UNIPROTO_UNI40N)
			/* Q.2971:Call-Control-N 4/39 */
			un0_setup(c, msg, u, CALLST_N1);
		else
			/* Q.2971:Call-Control-U 4/39 */
			un0_setup(c, msg, u, CALLST_U6);
		break;

	  case SIGC_CALL_PROC:
		if (c->cstate == CALLST_U1) {
			/* Q.2971:Call-Control-U 6/39 */
			u1n6_call_proc(c, msg, u, CALLST_U3);
			break;
		}
		if (c->cstate == CALLST_N6) {
			/* Q.2971:Call-Control-N 11/39 */
			u1n6_call_proc(c, msg, u, CALLST_N9);
			break;
		}
		(void)uni_decode_body(msg, u, &c->uni->cx);
		uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
		    &u->u.call_proc.epref, -1);
		goto drop;

	  case SIGC_ALERTING:
		if (c->cstate == CALLST_U1 || c->cstate == CALLST_U3) {
			/* Q.2971:Call-Control-U 37/39 (U1) */
			/* Q.2971:Call-Control-U 7/39 (U3) */
			unx_alerting(c, msg, u, CALLST_U4);
			break;
		}
		if (c->cstate == CALLST_N6) {
			/* Q.2971:Call-Control-N 9/39 (N6) */
			/* Q.2971:Call-Control-N 17/39 (N9) */
			unx_alerting(c, msg, u, CALLST_N7);
			break;
		}
		(void)uni_decode_body(msg, u, &c->uni->cx);
		uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
		    &u->u.alerting.epref, -1);
		goto drop;

	  case SIGC_CONNECT:
		if (c->cstate == CALLST_U1 || c->cstate == CALLST_U3 ||
		    c->cstate == CALLST_U4) {
			/* Q.2971:Call-Control-U 7-8/39  (U3) */
			/* Q.2971:Call-Control-U 11/39   (U4) */
			/* Q.2971:Call-Control-U 37/39   (U1) */
			unx_connect(c, msg, u, CALLST_U10);
			break;
		}
		if (c->cstate == CALLST_N6 || c->cstate == CALLST_N7 ||
		    c->cstate == CALLST_N9) {
			/* Q.2971:Call-Control-N 9-10/39 (N6) */
			/* Q.2971:Call-Control-N 14/39   (N7) */
			/* Q.2971:Call-Control-N 17/39   (N9) */
			unx_connect(c, msg, u, CALLST_N8);
			break;
		}
		(void)uni_decode_body(msg, u, &c->uni->cx);
		uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
		    &u->u.connect.epref, -1);
		goto drop;

	  case SIGC_CONNECT_ACK:
		if (c->cstate == CALLST_U8) {
			/* Q.2971:Call-Control-U 15-16/39 */
			u8_connect_ack(c, msg, u, CALLST_U10);
			break;
		}
		if (c->cstate == CALLST_N10) {
			/* Q.2971:Call-Control-N 18/39 */
			n10_connect_ack(c, msg, u);
			break;
		}
		uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP, NULL, 0);
		goto drop;

	  case SIGC_RELEASE:
		switch (c->cstate) {

		  default:
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP, NULL, 0);
			goto drop;

		  case CALLST_U11:
		  case CALLST_N12:
			/* Q.2971:Call-Control-U 28/39 */
			/* Q.2971:Call-Control-N 30/39 */
			u11n12_release(c, msg, u);
			break;

		  case CALLST_U1:
		  case CALLST_U3:
		  case CALLST_U4:
		  case CALLST_U6:
		  case CALLST_U7:
		  case CALLST_U8:
		  case CALLST_U9:
		  case CALLST_U10:
		  case CALLST_U12:
			/* Q.2971:Call-Control-U 25/39 */
			unx_release(c, msg, u, CALLST_U12);
			break;

		  case CALLST_N1:
		  case CALLST_N3:
		  case CALLST_N4:
		  case CALLST_N6:
		  case CALLST_N7:
		  case CALLST_N8:
		  case CALLST_N9:
		  case CALLST_N10:
		  case CALLST_N11:
			/* Q.2971:Call-Control-N 26/39 */
			unx_release(c, msg, u, CALLST_N11);
			break;
		}
		break;

	  case SIGC_RELEASE_COMPL:
		/* Q.2971:Call-Control-U 25/39 */
		/* Q.2971:Call-Control-N 26/39 */
		unx_release_compl(c, msg, u);
		break;

	  case SIGC_NOTIFY:
		/* Q.2971:Call-Control-U 18/39 */
		/* Q.2971:Call-Control-N 19/39 */
		unx_notify(c, msg, u);
		break;

	  case SIGC_STATUS:
		if (c->cstate == CALLST_U11 || c->cstate == CALLST_U12 ||
		    c->cstate == CALLST_N11 || c->cstate == CALLST_N12) {
			/* Q.2971:Call-Control-U 29/39 (U11) */
			/* Q.2971:Call-Control-U 30/39 (U12) */
			/* Q.2971:Call-Control-N 29/39 (N11) */
			/* Q.2971:Call-Control-N 31/39 (N12) */
			un11un12_status(c, msg, u);
			break;
		}
		/* Q.2971:Call-Control-U 32/39 */
		/* Q.2971:Call-Control-N 33/39 */
		unx_status(c, msg, u);
		break;

	  case SIGC_STATUS_ENQ:
		/* Q.2971:Call-Control-U 31/39 */
		/* Q.2971:Call-Control-N 32/39 */
		unx_status_enq(c, msg, u);
		break;

	  case SIGC_ADD_PARTY:
		(void)uni_decode_body(msg, u, &c->uni->cx);

		if (c->type != CALL_LEAF && c->type != CALL_ROOT) {
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.add_party.epref, UNI_EPSTATE_NULL);
			goto drop;
		}
		switch (c->cstate) {
		  case CALLST_U7:
		  case CALLST_U8:
		  case CALLST_U10:
		  case CALLST_N4:
		  case CALLST_N10:
			/* Q.2971:Call-Control-U 14/39  U7 */
			/* Q.2971:Call-Control-U 15/39  U8 */
			/* Q.2971:Call-Control-U 21/39  U10 */
			/* Q.2971:Call-Control-N 8/39   N4 */
			/* Q.2971:Call-Control-N 21/39  N10 */
			unx_add_party(c, msg, u, 1);
			break;

		  default:
			unx_add_party(c, msg, u, 0);
			goto drop;
		}
		break;

	  case SIGC_PARTY_ALERTING:
		(void)uni_decode_body(msg, u, &c->uni->cx);

		if (c->type != CALL_ROOT) {
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.party_alerting.epref, -1);
			goto drop;
		}
		switch (c->cstate) {

		  default:
			/* Q.2971 9.5.3.2.3a) */
			unx_party_alerting(c, msg, u, 0);
			break;

		  case CALLST_U4:
		  case CALLST_U10:
			/* Q.2971:Call-Control-U 9/39   U4 */
			/* Q.2971:Call-Control-U 21/39  U10 */
			/* Q.2971:Call-Control-N 12/39  N7 */
			/* Q.2971:Call-Control-N 15/39  N8 */
			/* Q.2971:Call-Control-N 22/39  N10 */
			unx_party_alerting(c, msg, u, 1);
			break;
		}
		break;

	  case SIGC_ADD_PARTY_ACK:
		(void)uni_decode_body(msg, u, &c->uni->cx);

		if (c->type != CALL_ROOT) {
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.add_party_rej.epref, -1);
			goto drop;
		}
		switch (c->cstate) {

		  case CALLST_U10:
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-N 15/39 N8 */
			/* Q.2971:Call-Control-N 22/39 N10 */
			un10n8_add_party_ack(c, msg, u, 1);
			break;

		  default:
			/* Q.2971 9.5.3.2.3a) */
			un10n8_add_party_ack(c, msg, u, 0);
			break;
		}
		break;

	  case SIGC_ADD_PARTY_REJ:
		(void)uni_decode_body(msg, u, &c->uni->cx);

		if (c->type != CALL_ROOT) {
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.add_party_rej.epref, -1);
			goto drop;
		}
		switch (c->cstate) {

		  case CALLST_U4:
	     	  case CALLST_U10:
		  case CALLST_N7:
		  case CALLST_N8:
		  case CALLST_N10:
			/* Q.2971:Call-Control-U 9/39 U4 */
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-N 12/39 N7 */
			/* Q.2971:Call-Control-N 15/39 N8 */
			/* Q.2971:Call-Control-N 22/39 N10 */
			unx_add_party_rej(c, msg, u, 1);
			break;

		  default:
			/* Q.2971: 9.5.3.2.3b */
			unx_add_party_rej(c, msg, u, 0);
			break;
		}
		break;

	  case SIGC_DROP_PARTY:
		(void)uni_decode_body(msg, u, &c->uni->cx);

		if (c->type != CALL_ROOT && c->type != CALL_LEAF) {
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.drop_party.epref, -1);
			goto drop;
		}
		switch (c->cstate) {
		  case CALLST_U11:
		  case CALLST_U12:
		  case CALLST_N11:
		  case CALLST_N12:
			/* Q.2971:Call-Control-U 28/39 U11 */
			/* Q.2971:Call-Control-U 30/39 U12 */
			/* Q.2971:Call-Control-N 29/39 N11 */
			/* Q.2971:Call-Control-N 30/39 N12 */
			goto drop;

		  case CALLST_NULL:
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.drop_party.epref, UNI_EPSTATE_NULL);
			goto drop;

		  case CALLST_U3:
		  case CALLST_N3:
			/* L3MU_17_38 */
			unx_drop_party(c, msg, u, 0);
			break;

		  case CALLST_U8:
			if (c->uni->sb_tb) {
				/* L3MU_06_0[3-6] */
				unx_drop_party(c, msg, u, 0);
				break;
			}
			/* FALLTHRU */

		  default:
			/* Q.2971:Call-Control-U 26/39 Ux */
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-N 27/39 Nx */
			/* Q.2971:Call-Control-N 21/39 N10 */
			unx_drop_party(c, msg, u, 1);
			break;
		}
		break;

	  case SIGC_DROP_PARTY_ACK:
		(void)uni_decode_body(msg, u, &c->uni->cx);

		if (c->type != CALL_ROOT && c->type != CALL_LEAF) {
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.drop_party_ack.epref, -1);
			goto drop;
		}
		switch (c->cstate) {

		  case CALLST_U11:
		  case CALLST_U12:
			/* Q.2971:Call-Control-U 28/39 U11 */
			/* Q.2971:Call-Control-U 30/39 U12 */
			/* Q.2971:Call-Control-N 29/39 N11 */
			/* Q.2971:Call-Control-N 30/39 N12 */
			goto drop;

		  case CALLST_NULL:
			uni_bad_message(c, u, UNI_CAUSE_MSG_INCOMP,
			    &u->u.drop_party.epref, UNI_EPSTATE_NULL);
			goto drop;

		  case CALLST_U4:
		  case CALLST_N4:
		  case CALLST_U7:
		  case CALLST_N7:
		  case CALLST_U8:
		  case CALLST_N8:
		  case CALLST_U10:
		  case CALLST_N10:
			/* Q.2971:Call-Control-U 26/39 Ux */
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-N 27/39 Nx */
			/* Q.2971:Call-Control-N 22/39 N10 */
			unx_drop_party_ack(c, msg, u, 1);
			break;

		  default:
			/* Q.2971 10.5 4th paragraph */
			unx_drop_party_ack(c, msg, u, 0);
			break;
		}
		break;

	  case SIGC_COBISETUP:	/* XXX */
		unx_unknown(c, msg, u);
		break;

	  /*
	   * User signals
	   */
	  case SIGC_SETUP_request:
		if (c->cstate == CALLST_NULL) {
			/* Q.2971:Call-Control-U 4/39 (U0) */
			/* Q.2971:Call-Control-N 4/39 (N0) */
			if (c->uni->proto == UNIPROTO_UNI40N)
				un0_setup_request(c, msg, cookie, CALLST_N6);
			else
				un0_setup_request(c, msg, cookie, CALLST_U1);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "setup.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_SETUP_response:
		if (c->cstate == CALLST_U6 || c->cstate == CALLST_U9 ||
		    c->cstate == CALLST_U7) {
			/* Q.2971:Call-Control-U 13/39	(U6) */
			/* Q.2971:Call-Control-U 14/39	(U7) */
			/* Q.2971:Call-Control-U 17/39	(U9) */
			unx_setup_response(c, msg, cookie, CALLST_U8);
			break;
		}
		if (c->cstate == CALLST_N1 || c->cstate == CALLST_N3 ||
		    c->cstate == CALLST_N4) {
			/* Q.2971:Call-Control-N 39/39  (N1) */
			/* Q.2971:Call-Control-N 7/39   (N3) */
			/* Q.2971:Call-Control-N 8/39   (N4) */
			unx_setup_response(c, msg, cookie, CALLST_N10);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "setup.response in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_SETUP_COMPLETE_request:
		if (c->cstate == CALLST_N8) {
			/* Q.2971:Call-Control-N 15/39 (N8) */
			n8_setup_compl_request(c, msg, cookie, CALLST_N10);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "setup_compl.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_PROCEEDING_request:
		if (c->cstate == CALLST_U6) {
			/* Q.2971:Call-Control-U 12/39 (U6) */
			u6n1_proceeding_request(c, msg, cookie, CALLST_U9);
			break;
		}
		if (c->cstate == CALLST_N1) {
			/* Q.2971:Call-Control-N 6/39 (N1) */
			u6n1_proceeding_request(c, msg, cookie, CALLST_N3);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "proceeding.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_ALERTING_request:
		if (c->cstate == CALLST_U6 || c->cstate == CALLST_U9) {
			/* Q.2971:Call-Control-U 13/39 (U6) */
			/* Q.2971:Call-Control-U 17/39 (U9) */
			unx_alerting_request(c, msg, cookie, CALLST_U7);
			break;
		}
		if (c->cstate == CALLST_N1 || c->cstate == CALLST_N3) {
			/* Q.2971:Call-Control-N 38/39 (N1) */
			/* Q.2971:Call-Control-N 7/39  (N3) */
			unx_alerting_request(c, msg, cookie, CALLST_N4);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "alerting.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_RELEASE_request:
		switch (c->cstate) {

		  case CALLST_U1:
		  case CALLST_U3:
		  case CALLST_U4:
		  case CALLST_U6:
		  case CALLST_U7:
		  case CALLST_U8:
		  case CALLST_U9:
		  case CALLST_U10:
			/* Q.2971:Call-Control-U 27/39 */
			unx_release_request(c, msg, cookie, CALLST_U11);
			break;

		  case CALLST_N1:
		  case CALLST_N3:
		  case CALLST_N4:
		  case CALLST_N6:
		  case CALLST_N7:
		  case CALLST_N8:
		  case CALLST_N9:
		  case CALLST_N10:
			/* Q.2971:Call-Control-N 28/39 */
			unx_release_request(c, msg, cookie, CALLST_N12);
			break;

		  case CALLST_U11:
		  case CALLST_U12:
		  case CALLST_N11:
		  case CALLST_N12:
		  case CALLST_NULL:
			VERBOSE(c->uni, UNI_FAC_ERR, 1,
			    "release.request in cs=%s",
			    callstates[c->cstate].name);
			uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE,
			    cookie);
			uni_msg_destroy(msg);
			break;
		}
		break;

	  case SIGC_RELEASE_response:
		if (c->cstate == CALLST_U6 || c->cstate == CALLST_U12 ||
		    c->cstate == CALLST_N1 || c->cstate == CALLST_N11) {
			/* Q.2971:Call-Control-U 12/39 (U6) */
			/* Q.2971:Call-Control-U 30/39 (U12) */
			/* Q.2971:Call-Control-N 6/39  (N1) */
			/* Q.2971:Call-Control-N 29/39 (N11) */
			unx_release_response(c, msg, cookie);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "release.response in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_NOTIFY_request:
		/* Q.2971:Call-Control-U 18/39 */
		/* Q.2971:Call-Control-N 19/39 */
		unx_notify_request(c, msg, cookie);
		break;

	  case SIGC_STATUS_ENQUIRY_request:
		/* Q.2971:Call-Control-U 31/39 */
		/* Q.2971:Call-Control-N 32/39 */
		unx_status_enquiry_request(c, msg, cookie);
		break;

	  case SIGC_ADD_PARTY_request:
		if (c->cstate == CALLST_U4 || c->cstate == CALLST_U10 ||
		    c->cstate == CALLST_N7 || c->cstate == CALLST_N10) {
			/* Q.2971:Call-Control-U 9-10/39 (U4) */
			/* Q.2971:Call-Control-U 21/39 (U10) */
			/* Q.2971:Call-Control-N 12/39 (N7) */
			/* Q.2971:Call-Control-N 22/39 (N10) */
			unx_add_party_request(c, msg, cookie);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "add-party.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_PARTY_ALERTING_request:
		if (c->cstate == CALLST_U7 || c->cstate == CALLST_U8 ||
		    c->cstate == CALLST_U10 ||
		    c->cstate == CALLST_N4 || c->cstate == CALLST_N10) {
			/* Q.2971:Call-Control-U 14/39 U7 */
			/* Q.2971:Call-Control-U 15/39 U8 */
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-N 8/39  N4 */
			/* Q.2971:Call-Control-N 22/39 N10 */
			unx_party_alerting_request(c, msg, cookie);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1,
		    "party-alerting.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_ADD_PARTY_ACK_request:
		if (c->cstate == CALLST_U10 || c->cstate == CALLST_N10) {
			/* Q.2971:Call-Control-U 21/39 (U10) */
			/* Q.2971:Call-Control-N 22/39 (N10)*/
			un10_add_party_ack_request(c, msg, cookie);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1,
		    "add-party-ack.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_ADD_PARTY_REJ_request:
		if (c->cstate == CALLST_U7 || c->cstate == CALLST_U8 ||
		    c->cstate == CALLST_U10 ||
		    c->cstate == CALLST_N4 || c->cstate == CALLST_N10) {
			/* Q.2971:Call-Control-U 14/39 U7 */
			/* Q.2971:Call-Control-U 15/39 U8 */
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-N 8/39  N4 */
			/* Q.2971:Call-Control-N 22/39 N10 */
			unx_add_party_rej_request(c, msg, cookie);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1,
		    "add-party-rej.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_DROP_PARTY_request:
		if (c->cstate != CALLST_U11 && c->cstate != CALLST_U12 &&
		    c->cstate != CALLST_N11 && c->cstate != CALLST_N12 &&
		    c->cstate != CALLST_NULL) {
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-U 26/39 U1-U9 */
			/* Q.2971:Call-Control-N 22/39 N10 */
			/* Q.2971:Call-Control-N 27/39 N1-N9 */
			unx_drop_party_request(c, msg, cookie);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "drop-party.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_DROP_PARTY_ACK_request:
		if (c->cstate != CALLST_U11 && c->cstate != CALLST_U12 &&
		    c->cstate != CALLST_N11 && c->cstate != CALLST_N12 &&
		    c->cstate != CALLST_NULL) {
			/* Q.2971:Call-Control-U 21/39 U10 */
			/* Q.2971:Call-Control-U 26/39 U1-U9 */
			/* Q.2971:Call-Control-N 22/39 N10 */
			/* Q.2971:Call-Control-N 27/39 N1-N9 */
			unx_drop_party_ack_request(c, msg, cookie);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1,
		    "drop-party-ack.request in cs=%s",
		    callstates[c->cstate].name);
		uniapi_call_error(c, UNIAPI_ERROR_BAD_CALLSTATE, cookie);
		uni_msg_destroy(msg);
		break;

	  case SIGC_ABORT_CALL_request:
	    {
		struct uni *uni = c->uni;

		uni_destroy_call(c, 0);
		uniapi_uni_error(uni, UNIAPI_OK, cookie, UNI_CALLSTATE_U0);
		break;
	    }

	  /*
	   * Timers
	   */
	  case SIGC_T301:
		if (c->cstate == CALLST_U4 || c->cstate == CALLST_N7) {
			/* Q.2971:Call-Control-U Missing */
			/* Q.2971:Call-Control-N 14/39 */
			u4n7_t301(c);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "T301 in cs=%s",
		    callstates[c->cstate].name);
		break;

	  case SIGC_T303:
		if (c->cstate == CALLST_U1 || c->cstate == CALLST_N6) {
			/* Q.2971:Call-Control-U 6/39 */
			/* Q.2971:Call-Control-N 11/39 */
			u1n6_t303(c);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "T303 in cs=%s",
		    callstates[c->cstate].name);
		break;

	  case SIGC_T308:
		if (c->cstate == CALLST_U11 || c->cstate == CALLST_N12) {
			/* Q.2971:Call-Control-U 28/39 */
			/* Q.2971:Call-Control-N 30/39 */
			u11n12_t308(c);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "T308 in cs=%s",
		    callstates[c->cstate].name);
		break;

	  case SIGC_T310:
		if (c->cstate == CALLST_U3 || c->cstate == CALLST_N9) {
			/* Q.2971:Call-Control-U 7/39 */
			/* Q.2971:Call-Control-N 17/39 */
			u3n9_t310(c);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "T310 in cs=%s",
		    callstates[c->cstate].name);
		break;

	  case SIGC_T313:
		if (c->cstate == CALLST_U8) {
			/* Q.2971:Call-Control-U 15/39 */
			u8_t313(c);
			break;
		}
		VERBOSE(c->uni, UNI_FAC_ERR, 1, "T313 in cs=%s",
		    callstates[c->cstate].name);
		break;

	  case SIGC_T322:
		/* Q.2971:Call-Control-U 34/39 */
		/* Q.2971:Call-Control-N 35/39 */
		unx_t322(c);
		break;

	  case SIGC_CALL_DELETE:
		CALL_FREE(c);
		break;

	  /*
	   * Party-Control
	   */
	  case SIGC_DROP_PARTY_indication:
		if (c->uni->proto == UNIPROTO_UNI40U)
			/* Q.2971:Call-Control-U 23/39 */
			ux_drop_party_indication(c, msg);
		else
			/* Q.2971:Call-Control-N 23/39 */
			nx_drop_party_indication(c, msg);
		break;

	  case SIGC_DROP_PARTY_ACK_indication:
		if (c->uni->proto == UNIPROTO_UNI40U)
			/* Q.2971:Call-Control-U 23/39 */
			ux_drop_party_ack_indication(c, msg);
		else
			/* Q.2971:Call-Control-N 23/39 */
			nx_drop_party_ack_indication(c, msg);
		break;

	  case SIGC_ADD_PARTY_REJ_indication:
		if (c->uni->proto == UNIPROTO_UNI40U)
			/* Q.2971:Call-Control-U 23/39 */
			ux_add_party_rej_indication(c, msg);
		else
			/* Q.2971:Call-Control-N 23/39 */
			nx_add_party_rej_indication(c, msg);
		break;


	  case SIGC_SEND_DROP_PARTY:
		/* Q.2971:Call-Control-U 21/39 */
		/* Q.2971:Call-Control-U 25/39 */
		if (uni_party_act_count(c, 2) != 0)
			(void)uni_send_output(u, c->uni);
		else if(c->cstate != CALLST_U11) {
			c->uni->cause = u->u.drop_party.cause;
			clear_callD(c);
		}
		UNI_FREE(u);
		break;

	  case SIGC_SEND_DROP_PARTY_ACK:
		/* Q.2971:Call-Control-U 21/39 */
		/* Q.2971:Call-Control-U 25/39 */
		if (uni_party_act_count(c, 2) != 0)
			(void)uni_send_output(u, c->uni);
		else if (c->cstate != CALLST_U11) {
			c->uni->cause = u->u.drop_party_ack.cause;
			clear_callD(c);
		}
		UNI_FREE(u);
		break;

	  case SIGC_SEND_ADD_PARTY_REJ:
		/* Q.2971:Call-Control-U 21/39 */
		/* Q.2971:Call-Control-U 24/39 */
		unx_send_add_party_rej(c, u);
		break;

	  case SIGC_SEND_STATUS_ENQ:
		/* Q.2971:Call-Control-U 21/39 */
		/* Q.2971:Call-Control-U 25/39 */
		unx_send_party_status_enq(c, u);
		break;

	  case SIGC_PARTY_DESTROYED:
		c->uni->funcs->uni_output(c->uni, c->uni->arg,
		    UNIAPI_PARTY_DESTROYED, cookie, msg);
		break;

	  case SIGC_END:
		break;
	}

	return;

  drop:
	/*
	 * This is for SAAL message signals that should be dropped.
	 */
	uni_msg_destroy(msg);
	UNI_FREE(u);
}