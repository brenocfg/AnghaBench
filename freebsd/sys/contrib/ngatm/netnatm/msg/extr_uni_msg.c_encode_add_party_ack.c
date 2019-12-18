#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_21__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  size_t u_int ;
struct unicx {int dummy; } ;
struct uni_msg {size_t* b_buf; size_t b_wptr; size_t b_rptr; } ;
struct TYPE_35__ {int present; } ;
struct TYPE_36__ {TYPE_21__ h; } ;
struct TYPE_32__ {int present; } ;
struct TYPE_34__ {TYPE_19__ h; } ;
struct TYPE_28__ {int present; } ;
struct TYPE_29__ {TYPE_15__ h; } ;
struct TYPE_26__ {int present; } ;
struct TYPE_27__ {TYPE_13__ h; } ;
struct TYPE_24__ {int present; } ;
struct TYPE_25__ {TYPE_11__ h; } ;
struct TYPE_44__ {int present; } ;
struct TYPE_23__ {TYPE_9__ h; } ;
struct TYPE_42__ {int present; } ;
struct TYPE_43__ {TYPE_7__ h; } ;
struct TYPE_40__ {int present; } ;
struct TYPE_41__ {TYPE_5__ h; } ;
struct TYPE_38__ {int present; } ;
struct TYPE_39__ {TYPE_3__ h; } ;
struct TYPE_33__ {int present; } ;
struct TYPE_37__ {TYPE_1__ h; } ;
struct uni_add_party_ack {TYPE_22__ unrec; TYPE_20__ called_soft; TYPE_18__* git; TYPE_16__ uu; TYPE_14__ connedsub; TYPE_12__ conned; TYPE_10__ eetd; TYPE_8__ notify; TYPE_6__ blli; TYPE_4__ aal; TYPE_2__ epref; int /*<<< orphan*/  hdr; } ;
struct TYPE_30__ {int present; } ;
struct TYPE_31__ {TYPE_17__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_ADD_PARTY_ACK ; 
 int UNI_IE_AAL ; 
 int UNI_IE_BLLI ; 
 int UNI_IE_CALLED_SOFT ; 
 int UNI_IE_CONNED ; 
 int UNI_IE_CONNEDSUB ; 
 int UNI_IE_EETD ; 
 int UNI_IE_EPREF ; 
 int UNI_IE_GIT ; 
 int UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_UNREC ; 
 int UNI_IE_UU ; 
 size_t UNI_NUM_IE_GIT ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,size_t*) ; 

__attribute__((used)) static int
encode_add_party_ack(struct uni_msg *msg, struct uni_add_party_ack *p, struct unicx *cx)
{
	u_int mlen;
	u_int i;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_ADD_PARTY_ACK, cx, &mlen))
		return (-2);

	if((p->epref.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EPREF, msg, (union uni_ieall *)&p->epref, cx))
		return (UNI_IE_EPREF);
	if((p->aal.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_AAL, msg, (union uni_ieall *)&p->aal, cx))
		return (UNI_IE_AAL);
	if((p->blli.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_BLLI, msg, (union uni_ieall *)&p->blli, cx))
		return (UNI_IE_BLLI);
	if((p->notify.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_NOTIFY, msg, (union uni_ieall *)&p->notify, cx))
		return (UNI_IE_NOTIFY);
	if((p->eetd.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EETD, msg, (union uni_ieall *)&p->eetd, cx))
		return (UNI_IE_EETD);
	if((p->conned.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CONNED, msg, (union uni_ieall *)&p->conned, cx))
		return (UNI_IE_CONNED);
	if((p->connedsub.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CONNEDSUB, msg, (union uni_ieall *)&p->connedsub, cx))
		return (UNI_IE_CONNEDSUB);
	if((p->uu.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UU, msg, (union uni_ieall *)&p->uu, cx))
		return (UNI_IE_UU);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if((p->git[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_GIT, msg, (union uni_ieall *)&p->git[i], cx))
		return ((i << 16) + UNI_IE_GIT);
	if((p->called_soft.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLED_SOFT, msg, (union uni_ieall *)&p->called_soft, cx))
		return (UNI_IE_CALLED_SOFT);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}