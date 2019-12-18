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
struct TYPE_72__ {int present; } ;
struct TYPE_74__ {TYPE_39__ h; } ;
struct TYPE_68__ {int present; } ;
struct TYPE_69__ {TYPE_35__ h; } ;
struct TYPE_66__ {int present; } ;
struct TYPE_67__ {TYPE_33__ h; } ;
struct TYPE_64__ {int present; } ;
struct TYPE_65__ {TYPE_31__ h; } ;
struct TYPE_61__ {int present; } ;
struct TYPE_63__ {TYPE_29__ h; } ;
struct TYPE_57__ {int present; } ;
struct TYPE_58__ {TYPE_25__ h; } ;
struct TYPE_55__ {int present; } ;
struct TYPE_56__ {TYPE_23__ h; } ;
struct TYPE_53__ {int present; } ;
struct TYPE_54__ {TYPE_21__ h; } ;
struct TYPE_50__ {int present; } ;
struct TYPE_52__ {TYPE_19__ h; } ;
struct TYPE_46__ {int present; } ;
struct TYPE_47__ {TYPE_15__ h; } ;
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
struct uni_add_party {TYPE_40__ unrec; TYPE_38__* dtl; TYPE_36__ dtl_repeat; TYPE_34__ called_soft; TYPE_32__ calling_soft; TYPE_30__ lij_seqno; TYPE_28__* git; TYPE_26__ uu; TYPE_24__ eetd; TYPE_22__ notify; TYPE_20__ epref; TYPE_18__* tns; TYPE_16__ scompl; TYPE_14__* callingsub; TYPE_12__ calling; TYPE_10__* calledsub; TYPE_8__ called; TYPE_6__ blli; TYPE_4__ bhli; TYPE_2__ aal; } ;
struct TYPE_80__ {int present; } ;
struct TYPE_70__ {int present; } ;
struct TYPE_71__ {TYPE_37__ h; } ;
struct TYPE_59__ {int present; } ;
struct TYPE_60__ {TYPE_27__ h; } ;
struct TYPE_48__ {int present; } ;
struct TYPE_49__ {TYPE_17__ h; } ;
struct TYPE_44__ {int present; } ;
struct TYPE_45__ {TYPE_13__ h; } ;
struct TYPE_41__ {TYPE_9__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_AAL ; 
 int /*<<< orphan*/  UNI_IE_BHLI ; 
 int /*<<< orphan*/  UNI_IE_BLLI ; 
 int /*<<< orphan*/  UNI_IE_CALLED ; 
 int /*<<< orphan*/  UNI_IE_CALLEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CALLED_SOFT ; 
 int /*<<< orphan*/  UNI_IE_CALLING ; 
 int /*<<< orphan*/  UNI_IE_CALLINGSUB ; 
 int /*<<< orphan*/  UNI_IE_CALLING_SOFT ; 
 int /*<<< orphan*/  UNI_IE_DTL ; 
 int /*<<< orphan*/  UNI_IE_EETD ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_LIJ_SEQNO ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_REPEAT ; 
 int /*<<< orphan*/  UNI_IE_SCOMPL ; 
 int /*<<< orphan*/  UNI_IE_TNS ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 size_t UNI_NUM_IE_CALLEDSUB ; 
 size_t UNI_NUM_IE_CALLINGSUB ; 
 size_t UNI_NUM_IE_DTL ; 
 size_t UNI_NUM_IE_GIT ; 
 size_t UNI_NUM_IE_TNS ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_add_party(struct uni_add_party *msg, struct unicx *cx)
{
	u_int i;

	if(msg->aal.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_AAL, (union uni_ieall *)&msg->aal, cx);
	if(msg->bhli.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_BHLI, (union uni_ieall *)&msg->bhli, cx);
	if(msg->blli.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_BLLI, (union uni_ieall *)&msg->blli, cx);
	if(msg->called.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLED, (union uni_ieall *)&msg->called, cx);
	for(i = 0; i < UNI_NUM_IE_CALLEDSUB; i++)
		if(msg->calledsub[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_CALLEDSUB, (union uni_ieall *)&msg->calledsub[i], cx);
	if(msg->calling.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLING, (union uni_ieall *)&msg->calling, cx);
	for(i = 0; i < UNI_NUM_IE_CALLINGSUB; i++)
		if(msg->callingsub[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_CALLINGSUB, (union uni_ieall *)&msg->callingsub[i], cx);
	if(msg->scompl.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_SCOMPL, (union uni_ieall *)&msg->scompl, cx);
	for(i = 0; i < UNI_NUM_IE_TNS; i++)
		if(msg->tns[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_TNS, (union uni_ieall *)&msg->tns[i], cx);
	if(msg->epref.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EPREF, (union uni_ieall *)&msg->epref, cx);
	if(msg->notify.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_NOTIFY, (union uni_ieall *)&msg->notify, cx);
	if(msg->eetd.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EETD, (union uni_ieall *)&msg->eetd, cx);
	if(msg->uu.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UU, (union uni_ieall *)&msg->uu, cx);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if(msg->git[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_GIT, (union uni_ieall *)&msg->git[i], cx);
	if(msg->lij_seqno.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_LIJ_SEQNO, (union uni_ieall *)&msg->lij_seqno, cx);
	if(msg->calling_soft.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLING_SOFT, (union uni_ieall *)&msg->calling_soft, cx);
	if(msg->called_soft.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLED_SOFT, (union uni_ieall *)&msg->called_soft, cx);
	if(msg->dtl_repeat.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_REPEAT, (union uni_ieall *)&msg->dtl_repeat, cx);
	for(i = 0; i < UNI_NUM_IE_DTL; i++)
		if(msg->dtl[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_DTL, (union uni_ieall *)&msg->dtl[i], cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}