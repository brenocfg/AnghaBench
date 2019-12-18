#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  size_t u_int ;
struct unicx {int dummy; } ;
struct uni_msg {size_t* b_buf; size_t b_wptr; size_t b_rptr; } ;
struct TYPE_22__ {int present; } ;
struct TYPE_23__ {TYPE_15__ h; } ;
struct TYPE_20__ {int present; } ;
struct TYPE_21__ {TYPE_13__ h; } ;
struct TYPE_18__ {int present; } ;
struct TYPE_19__ {TYPE_11__ h; } ;
struct TYPE_30__ {int present; } ;
struct TYPE_31__ {TYPE_7__ h; } ;
struct TYPE_26__ {int present; } ;
struct TYPE_27__ {TYPE_3__ h; } ;
struct uni_leaf_setup_req {TYPE_16__ unrec; TYPE_14__ lij_seqno; TYPE_12__ lij_callid; TYPE_10__* calledsub; TYPE_8__ called; TYPE_6__* callingsub; TYPE_4__ calling; TYPE_2__* tns; int /*<<< orphan*/  hdr; } ;
struct TYPE_32__ {int present; } ;
struct TYPE_28__ {int present; } ;
struct TYPE_29__ {TYPE_5__ h; } ;
struct TYPE_24__ {int present; } ;
struct TYPE_25__ {TYPE_1__ h; } ;
struct TYPE_17__ {TYPE_9__ h; } ;

/* Variables and functions */
 int UNI_IE_CALLED ; 
 int UNI_IE_CALLEDSUB ; 
 int UNI_IE_CALLING ; 
 int UNI_IE_CALLINGSUB ; 
 int UNI_IE_LIJ_CALLID ; 
 int UNI_IE_LIJ_SEQNO ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_TNS ; 
 int UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_LEAF_SETUP_REQ ; 
 size_t UNI_NUM_IE_CALLEDSUB ; 
 size_t UNI_NUM_IE_CALLINGSUB ; 
 size_t UNI_NUM_IE_TNS ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,size_t*) ; 

__attribute__((used)) static int
encode_leaf_setup_req(struct uni_msg *msg, struct uni_leaf_setup_req *p, struct unicx *cx)
{
	u_int mlen;
	u_int i;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_LEAF_SETUP_REQ, cx, &mlen))
		return (-2);

	for(i = 0; i < UNI_NUM_IE_TNS; i++)
		if((p->tns[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_TNS, msg, (union uni_ieall *)&p->tns[i], cx))
		return ((i << 16) + UNI_IE_TNS);
	if((p->calling.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLING, msg, (union uni_ieall *)&p->calling, cx))
		return (UNI_IE_CALLING);
	for(i = 0; i < UNI_NUM_IE_CALLINGSUB; i++)
		if((p->callingsub[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_CALLINGSUB, msg, (union uni_ieall *)&p->callingsub[i], cx))
		return ((i << 16) + UNI_IE_CALLINGSUB);
	if((p->called.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLED, msg, (union uni_ieall *)&p->called, cx))
		return (UNI_IE_CALLED);
	for(i = 0; i < UNI_NUM_IE_CALLEDSUB; i++)
		if((p->calledsub[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_CALLEDSUB, msg, (union uni_ieall *)&p->calledsub[i], cx))
		return ((i << 16) + UNI_IE_CALLEDSUB);
	if((p->lij_callid.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_LIJ_CALLID, msg, (union uni_ieall *)&p->lij_callid, cx))
		return (UNI_IE_LIJ_CALLID);
	if((p->lij_seqno.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_LIJ_SEQNO, msg, (union uni_ieall *)&p->lij_seqno, cx))
		return (UNI_IE_LIJ_SEQNO);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}