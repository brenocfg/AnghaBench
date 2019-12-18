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
struct uni_connect {TYPE_36__ unrec; TYPE_34__ report; TYPE_32__ called_soft; TYPE_30__ abradd; TYPE_28__ abrsetup; TYPE_26__ facility; TYPE_24__ exqos; TYPE_22__ traffic; TYPE_20__ uu; TYPE_18__* git; TYPE_16__ eetd; TYPE_14__ connedsub; TYPE_12__ conned; TYPE_10__ notify; TYPE_8__ epref; TYPE_6__ connid; TYPE_4__ blli; TYPE_2__ aal; } ;
struct TYPE_44__ {int present; } ;
struct TYPE_45__ {TYPE_17__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_AAL ; 
 int /*<<< orphan*/  UNI_IE_ABRADD ; 
 int /*<<< orphan*/  UNI_IE_ABRSETUP ; 
 int /*<<< orphan*/  UNI_IE_BLLI ; 
 int /*<<< orphan*/  UNI_IE_CALLED_SOFT ; 
 int /*<<< orphan*/  UNI_IE_CONNED ; 
 int /*<<< orphan*/  UNI_IE_CONNEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CONNID ; 
 int /*<<< orphan*/  UNI_IE_EETD ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_EXQOS ; 
 int /*<<< orphan*/  UNI_IE_FACILITY ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_REPORT ; 
 int /*<<< orphan*/  UNI_IE_TRAFFIC ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 size_t UNI_NUM_IE_GIT ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_connect(struct uni_connect *msg, struct unicx *cx)
{
	u_int i;

	if(msg->aal.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_AAL, (union uni_ieall *)&msg->aal, cx);
	if(msg->blli.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_BLLI, (union uni_ieall *)&msg->blli, cx);
	if(msg->connid.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CONNID, (union uni_ieall *)&msg->connid, cx);
	if(msg->epref.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EPREF, (union uni_ieall *)&msg->epref, cx);
	if(msg->notify.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_NOTIFY, (union uni_ieall *)&msg->notify, cx);
	if(msg->conned.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CONNED, (union uni_ieall *)&msg->conned, cx);
	if(msg->connedsub.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CONNEDSUB, (union uni_ieall *)&msg->connedsub, cx);
	if(msg->eetd.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EETD, (union uni_ieall *)&msg->eetd, cx);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if(msg->git[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_GIT, (union uni_ieall *)&msg->git[i], cx);
	if(msg->uu.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UU, (union uni_ieall *)&msg->uu, cx);
	if(msg->traffic.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_TRAFFIC, (union uni_ieall *)&msg->traffic, cx);
	if(msg->exqos.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EXQOS, (union uni_ieall *)&msg->exqos, cx);
	if(msg->facility.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_FACILITY, (union uni_ieall *)&msg->facility, cx);
	if(msg->abrsetup.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_ABRSETUP, (union uni_ieall *)&msg->abrsetup, cx);
	if(msg->abradd.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_ABRADD, (union uni_ieall *)&msg->abradd, cx);
	if(msg->called_soft.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLED_SOFT, (union uni_ieall *)&msg->called_soft, cx);
	if(msg->report.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_REPORT, (union uni_ieall *)&msg->report, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}