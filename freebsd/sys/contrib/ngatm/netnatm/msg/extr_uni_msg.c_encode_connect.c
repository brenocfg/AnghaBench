#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_72__   TYPE_9__ ;
typedef  struct TYPE_71__   TYPE_8__ ;
typedef  struct TYPE_70__   TYPE_7__ ;
typedef  struct TYPE_69__   TYPE_6__ ;
typedef  struct TYPE_68__   TYPE_5__ ;
typedef  struct TYPE_67__   TYPE_4__ ;
typedef  struct TYPE_66__   TYPE_3__ ;
typedef  struct TYPE_65__   TYPE_36__ ;
typedef  struct TYPE_64__   TYPE_35__ ;
typedef  struct TYPE_63__   TYPE_34__ ;
typedef  struct TYPE_62__   TYPE_33__ ;
typedef  struct TYPE_61__   TYPE_32__ ;
typedef  struct TYPE_60__   TYPE_31__ ;
typedef  struct TYPE_59__   TYPE_30__ ;
typedef  struct TYPE_58__   TYPE_2__ ;
typedef  struct TYPE_57__   TYPE_29__ ;
typedef  struct TYPE_56__   TYPE_28__ ;
typedef  struct TYPE_55__   TYPE_27__ ;
typedef  struct TYPE_54__   TYPE_26__ ;
typedef  struct TYPE_53__   TYPE_25__ ;
typedef  struct TYPE_52__   TYPE_24__ ;
typedef  struct TYPE_51__   TYPE_23__ ;
typedef  struct TYPE_50__   TYPE_22__ ;
typedef  struct TYPE_49__   TYPE_21__ ;
typedef  struct TYPE_48__   TYPE_20__ ;
typedef  struct TYPE_47__   TYPE_1__ ;
typedef  struct TYPE_46__   TYPE_19__ ;
typedef  struct TYPE_45__   TYPE_18__ ;
typedef  struct TYPE_44__   TYPE_17__ ;
typedef  struct TYPE_43__   TYPE_16__ ;
typedef  struct TYPE_42__   TYPE_15__ ;
typedef  struct TYPE_41__   TYPE_14__ ;
typedef  struct TYPE_40__   TYPE_13__ ;
typedef  struct TYPE_39__   TYPE_12__ ;
typedef  struct TYPE_38__   TYPE_11__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  size_t u_int ;
struct unicx {int dummy; } ;
struct uni_msg {size_t* b_buf; size_t b_wptr; size_t b_rptr; } ;
struct TYPE_64__ {int present; } ;
struct TYPE_65__ {TYPE_35__ h; } ;
struct TYPE_62__ {int present; } ;
struct TYPE_63__ {TYPE_33__ h; } ;
struct TYPE_60__ {int present; } ;
struct TYPE_61__ {TYPE_31__ h; } ;
struct TYPE_57__ {int present; } ;
struct TYPE_59__ {TYPE_29__ h; } ;
struct TYPE_55__ {int present; } ;
struct TYPE_56__ {TYPE_27__ h; } ;
struct TYPE_53__ {int present; } ;
struct TYPE_54__ {TYPE_25__ h; } ;
struct TYPE_51__ {int present; } ;
struct TYPE_52__ {TYPE_23__ h; } ;
struct TYPE_49__ {int present; } ;
struct TYPE_50__ {TYPE_21__ h; } ;
struct TYPE_46__ {int present; } ;
struct TYPE_48__ {TYPE_19__ h; } ;
struct TYPE_42__ {int present; } ;
struct TYPE_43__ {TYPE_15__ h; } ;
struct TYPE_40__ {int present; } ;
struct TYPE_41__ {TYPE_13__ h; } ;
struct TYPE_38__ {int present; } ;
struct TYPE_39__ {TYPE_11__ h; } ;
struct TYPE_72__ {int present; } ;
struct TYPE_37__ {TYPE_9__ h; } ;
struct TYPE_70__ {int present; } ;
struct TYPE_71__ {TYPE_7__ h; } ;
struct TYPE_68__ {int present; } ;
struct TYPE_69__ {TYPE_5__ h; } ;
struct TYPE_66__ {int present; } ;
struct TYPE_67__ {TYPE_3__ h; } ;
struct TYPE_47__ {int present; } ;
struct TYPE_58__ {TYPE_1__ h; } ;
struct uni_connect {TYPE_36__ unrec; TYPE_34__ report; TYPE_32__ called_soft; TYPE_30__ abradd; TYPE_28__ abrsetup; TYPE_26__ facility; TYPE_24__ exqos; TYPE_22__ traffic; TYPE_20__ uu; TYPE_18__* git; TYPE_16__ eetd; TYPE_14__ connedsub; TYPE_12__ conned; TYPE_10__ notify; TYPE_8__ epref; TYPE_6__ connid; TYPE_4__ blli; TYPE_2__ aal; int /*<<< orphan*/  hdr; } ;
struct TYPE_44__ {int present; } ;
struct TYPE_45__ {TYPE_17__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_CONNECT ; 
 int UNI_IE_AAL ; 
 int UNI_IE_ABRADD ; 
 int UNI_IE_ABRSETUP ; 
 int UNI_IE_BLLI ; 
 int UNI_IE_CALLED_SOFT ; 
 int UNI_IE_CONNED ; 
 int UNI_IE_CONNEDSUB ; 
 int UNI_IE_CONNID ; 
 int UNI_IE_EETD ; 
 int UNI_IE_EPREF ; 
 int UNI_IE_EXQOS ; 
 int UNI_IE_FACILITY ; 
 int UNI_IE_GIT ; 
 int UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_REPORT ; 
 int UNI_IE_TRAFFIC ; 
 int UNI_IE_UNREC ; 
 int UNI_IE_UU ; 
 size_t UNI_NUM_IE_GIT ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,size_t*) ; 

__attribute__((used)) static int
encode_connect(struct uni_msg *msg, struct uni_connect *p, struct unicx *cx)
{
	u_int mlen;
	u_int i;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_CONNECT, cx, &mlen))
		return (-2);

	if((p->aal.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_AAL, msg, (union uni_ieall *)&p->aal, cx))
		return (UNI_IE_AAL);
	if((p->blli.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_BLLI, msg, (union uni_ieall *)&p->blli, cx))
		return (UNI_IE_BLLI);
	if((p->connid.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CONNID, msg, (union uni_ieall *)&p->connid, cx))
		return (UNI_IE_CONNID);
	if((p->epref.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EPREF, msg, (union uni_ieall *)&p->epref, cx))
		return (UNI_IE_EPREF);
	if((p->notify.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_NOTIFY, msg, (union uni_ieall *)&p->notify, cx))
		return (UNI_IE_NOTIFY);
	if((p->conned.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CONNED, msg, (union uni_ieall *)&p->conned, cx))
		return (UNI_IE_CONNED);
	if((p->connedsub.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CONNEDSUB, msg, (union uni_ieall *)&p->connedsub, cx))
		return (UNI_IE_CONNEDSUB);
	if((p->eetd.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EETD, msg, (union uni_ieall *)&p->eetd, cx))
		return (UNI_IE_EETD);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if((p->git[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_GIT, msg, (union uni_ieall *)&p->git[i], cx))
		return ((i << 16) + UNI_IE_GIT);
	if((p->uu.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UU, msg, (union uni_ieall *)&p->uu, cx))
		return (UNI_IE_UU);
	if((p->traffic.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_TRAFFIC, msg, (union uni_ieall *)&p->traffic, cx))
		return (UNI_IE_TRAFFIC);
	if((p->exqos.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EXQOS, msg, (union uni_ieall *)&p->exqos, cx))
		return (UNI_IE_EXQOS);
	if((p->facility.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_FACILITY, msg, (union uni_ieall *)&p->facility, cx))
		return (UNI_IE_FACILITY);
	if((p->abrsetup.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_ABRSETUP, msg, (union uni_ieall *)&p->abrsetup, cx))
		return (UNI_IE_ABRSETUP);
	if((p->abradd.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_ABRADD, msg, (union uni_ieall *)&p->abradd, cx))
		return (UNI_IE_ABRADD);
	if((p->called_soft.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLED_SOFT, msg, (union uni_ieall *)&p->called_soft, cx))
		return (UNI_IE_CALLED_SOFT);
	if((p->report.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_REPORT, msg, (union uni_ieall *)&p->report, cx))
		return (UNI_IE_REPORT);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}