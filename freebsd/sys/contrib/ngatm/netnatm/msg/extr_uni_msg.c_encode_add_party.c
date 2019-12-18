#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_80__   TYPE_9__ ;
typedef  struct TYPE_79__   TYPE_8__ ;
typedef  struct TYPE_78__   TYPE_7__ ;
typedef  struct TYPE_77__   TYPE_6__ ;
typedef  struct TYPE_76__   TYPE_5__ ;
typedef  struct TYPE_75__   TYPE_4__ ;
typedef  struct TYPE_74__   TYPE_40__ ;
typedef  struct TYPE_73__   TYPE_3__ ;
typedef  struct TYPE_72__   TYPE_39__ ;
typedef  struct TYPE_71__   TYPE_38__ ;
typedef  struct TYPE_70__   TYPE_37__ ;
typedef  struct TYPE_69__   TYPE_36__ ;
typedef  struct TYPE_68__   TYPE_35__ ;
typedef  struct TYPE_67__   TYPE_34__ ;
typedef  struct TYPE_66__   TYPE_33__ ;
typedef  struct TYPE_65__   TYPE_32__ ;
typedef  struct TYPE_64__   TYPE_31__ ;
typedef  struct TYPE_63__   TYPE_30__ ;
typedef  struct TYPE_62__   TYPE_2__ ;
typedef  struct TYPE_61__   TYPE_29__ ;
typedef  struct TYPE_60__   TYPE_28__ ;
typedef  struct TYPE_59__   TYPE_27__ ;
typedef  struct TYPE_58__   TYPE_26__ ;
typedef  struct TYPE_57__   TYPE_25__ ;
typedef  struct TYPE_56__   TYPE_24__ ;
typedef  struct TYPE_55__   TYPE_23__ ;
typedef  struct TYPE_54__   TYPE_22__ ;
typedef  struct TYPE_53__   TYPE_21__ ;
typedef  struct TYPE_52__   TYPE_20__ ;
typedef  struct TYPE_51__   TYPE_1__ ;
typedef  struct TYPE_50__   TYPE_19__ ;
typedef  struct TYPE_49__   TYPE_18__ ;
typedef  struct TYPE_48__   TYPE_17__ ;
typedef  struct TYPE_47__   TYPE_16__ ;
typedef  struct TYPE_46__   TYPE_15__ ;
typedef  struct TYPE_45__   TYPE_14__ ;
typedef  struct TYPE_44__   TYPE_13__ ;
typedef  struct TYPE_43__   TYPE_12__ ;
typedef  struct TYPE_42__   TYPE_11__ ;
typedef  struct TYPE_41__   TYPE_10__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  size_t u_int ;
struct unicx {int dummy; } ;
struct uni_msg {size_t* b_buf; size_t b_wptr; size_t b_rptr; } ;
struct TYPE_42__ {int present; } ;
struct TYPE_43__ {TYPE_11__ h; } ;
struct TYPE_78__ {int present; } ;
struct TYPE_79__ {TYPE_7__ h; } ;
struct TYPE_76__ {int present; } ;
struct TYPE_77__ {TYPE_5__ h; } ;
struct TYPE_73__ {int present; } ;
struct TYPE_75__ {TYPE_3__ h; } ;
struct TYPE_51__ {int present; } ;
struct TYPE_62__ {TYPE_1__ h; } ;
struct TYPE_70__ {int present; } ;
struct TYPE_71__ {TYPE_37__ h; } ;
struct TYPE_68__ {int present; } ;
struct TYPE_69__ {TYPE_35__ h; } ;
struct TYPE_66__ {int present; } ;
struct TYPE_67__ {TYPE_33__ h; } ;
struct TYPE_64__ {int present; } ;
struct TYPE_65__ {TYPE_31__ h; } ;
struct TYPE_59__ {int present; } ;
struct TYPE_60__ {TYPE_27__ h; } ;
struct TYPE_55__ {int present; } ;
struct TYPE_56__ {TYPE_23__ h; } ;
struct TYPE_50__ {int present; } ;
struct TYPE_52__ {TYPE_19__ h; } ;
struct TYPE_48__ {int present; } ;
struct TYPE_49__ {TYPE_17__ h; } ;
struct TYPE_46__ {int present; } ;
struct TYPE_47__ {TYPE_15__ h; } ;
struct TYPE_44__ {int present; } ;
struct TYPE_45__ {TYPE_13__ h; } ;
struct uni_add_party {TYPE_12__ unrec; TYPE_10__* dtl; TYPE_8__ dtl_repeat; TYPE_6__ called_soft; TYPE_4__ calling_soft; TYPE_2__ lij_seqno; TYPE_40__* git; TYPE_38__ uu; TYPE_36__ eetd; TYPE_34__ notify; TYPE_32__ epref; TYPE_30__* tns; TYPE_28__ scompl; TYPE_26__* callingsub; TYPE_24__ calling; TYPE_22__* calledsub; TYPE_20__ called; TYPE_18__ blli; TYPE_16__ bhli; TYPE_14__ aal; int /*<<< orphan*/  hdr; } ;
struct TYPE_80__ {int present; } ;
struct TYPE_72__ {int present; } ;
struct TYPE_74__ {TYPE_39__ h; } ;
struct TYPE_61__ {int present; } ;
struct TYPE_63__ {TYPE_29__ h; } ;
struct TYPE_57__ {int present; } ;
struct TYPE_58__ {TYPE_25__ h; } ;
struct TYPE_53__ {int present; } ;
struct TYPE_54__ {TYPE_21__ h; } ;
struct TYPE_41__ {TYPE_9__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_ADD_PARTY ; 
 int UNI_IE_AAL ; 
 int UNI_IE_BHLI ; 
 int UNI_IE_BLLI ; 
 int UNI_IE_CALLED ; 
 int UNI_IE_CALLEDSUB ; 
 int UNI_IE_CALLED_SOFT ; 
 int UNI_IE_CALLING ; 
 int UNI_IE_CALLINGSUB ; 
 int UNI_IE_CALLING_SOFT ; 
 int UNI_IE_DTL ; 
 int UNI_IE_EETD ; 
 int UNI_IE_EPREF ; 
 int UNI_IE_GIT ; 
 int UNI_IE_LIJ_SEQNO ; 
 int UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_SCOMPL ; 
 int UNI_IE_TNS ; 
 int UNI_IE_UNREC ; 
 int UNI_IE_UU ; 
 size_t UNI_NUM_IE_CALLEDSUB ; 
 size_t UNI_NUM_IE_CALLINGSUB ; 
 size_t UNI_NUM_IE_DTL ; 
 size_t UNI_NUM_IE_GIT ; 
 size_t UNI_NUM_IE_TNS ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,size_t*) ; 

__attribute__((used)) static int
encode_add_party(struct uni_msg *msg, struct uni_add_party *p, struct unicx *cx)
{
	u_int mlen;
	u_int i;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_ADD_PARTY, cx, &mlen))
		return (-2);

	if((p->aal.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_AAL, msg, (union uni_ieall *)&p->aal, cx))
		return (UNI_IE_AAL);
	if((p->bhli.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_BHLI, msg, (union uni_ieall *)&p->bhli, cx))
		return (UNI_IE_BHLI);
	if((p->blli.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_BLLI, msg, (union uni_ieall *)&p->blli, cx))
		return (UNI_IE_BLLI);
	if((p->called.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLED, msg, (union uni_ieall *)&p->called, cx))
		return (UNI_IE_CALLED);
	for(i = 0; i < UNI_NUM_IE_CALLEDSUB; i++)
		if((p->calledsub[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_CALLEDSUB, msg, (union uni_ieall *)&p->calledsub[i], cx))
		return ((i << 16) + UNI_IE_CALLEDSUB);
	if((p->calling.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLING, msg, (union uni_ieall *)&p->calling, cx))
		return (UNI_IE_CALLING);
	for(i = 0; i < UNI_NUM_IE_CALLINGSUB; i++)
		if((p->callingsub[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_CALLINGSUB, msg, (union uni_ieall *)&p->callingsub[i], cx))
		return ((i << 16) + UNI_IE_CALLINGSUB);
	if((p->scompl.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_SCOMPL, msg, (union uni_ieall *)&p->scompl, cx))
		return (UNI_IE_SCOMPL);
	for(i = 0; i < UNI_NUM_IE_TNS; i++)
		if((p->tns[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_TNS, msg, (union uni_ieall *)&p->tns[i], cx))
		return ((i << 16) + UNI_IE_TNS);
	if((p->epref.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EPREF, msg, (union uni_ieall *)&p->epref, cx))
		return (UNI_IE_EPREF);
	if((p->notify.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_NOTIFY, msg, (union uni_ieall *)&p->notify, cx))
		return (UNI_IE_NOTIFY);
	if((p->eetd.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EETD, msg, (union uni_ieall *)&p->eetd, cx))
		return (UNI_IE_EETD);
	if((p->uu.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UU, msg, (union uni_ieall *)&p->uu, cx))
		return (UNI_IE_UU);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if((p->git[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_GIT, msg, (union uni_ieall *)&p->git[i], cx))
		return ((i << 16) + UNI_IE_GIT);
	if((p->lij_seqno.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_LIJ_SEQNO, msg, (union uni_ieall *)&p->lij_seqno, cx))
		return (UNI_IE_LIJ_SEQNO);
	if((p->calling_soft.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLING_SOFT, msg, (union uni_ieall *)&p->calling_soft, cx))
		return (UNI_IE_CALLING_SOFT);
	if((p->called_soft.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLED_SOFT, msg, (union uni_ieall *)&p->called_soft, cx))
		return (UNI_IE_CALLED_SOFT);
	if((p->dtl_repeat.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_DTL, msg, (union uni_ieall *)&p->dtl_repeat, cx))
		return (0x10000000 + UNI_IE_DTL);
	for(i = 0; i < UNI_NUM_IE_DTL; i++)
		if((p->dtl[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_DTL, msg, (union uni_ieall *)&p->dtl[i], cx))
		return ((i << 16) + UNI_IE_DTL);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}