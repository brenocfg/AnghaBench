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
struct uni_add_party_ack {TYPE_22__ unrec; TYPE_20__ called_soft; TYPE_18__* git; TYPE_16__ uu; TYPE_14__ connedsub; TYPE_12__ conned; TYPE_10__ eetd; TYPE_8__ notify; TYPE_6__ blli; TYPE_4__ aal; TYPE_2__ epref; } ;
struct TYPE_30__ {int present; } ;
struct TYPE_31__ {TYPE_17__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_AAL ; 
 int /*<<< orphan*/  UNI_IE_BLLI ; 
 int /*<<< orphan*/  UNI_IE_CALLED_SOFT ; 
 int /*<<< orphan*/  UNI_IE_CONNED ; 
 int /*<<< orphan*/  UNI_IE_CONNEDSUB ; 
 int /*<<< orphan*/  UNI_IE_EETD ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 size_t UNI_NUM_IE_GIT ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_add_party_ack(struct uni_add_party_ack *msg, struct unicx *cx)
{
	u_int i;

	if(msg->epref.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EPREF, (union uni_ieall *)&msg->epref, cx);
	if(msg->aal.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_AAL, (union uni_ieall *)&msg->aal, cx);
	if(msg->blli.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_BLLI, (union uni_ieall *)&msg->blli, cx);
	if(msg->notify.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_NOTIFY, (union uni_ieall *)&msg->notify, cx);
	if(msg->eetd.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EETD, (union uni_ieall *)&msg->eetd, cx);
	if(msg->conned.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CONNED, (union uni_ieall *)&msg->conned, cx);
	if(msg->connedsub.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CONNEDSUB, (union uni_ieall *)&msg->connedsub, cx);
	if(msg->uu.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UU, (union uni_ieall *)&msg->uu, cx);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if(msg->git[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_GIT, (union uni_ieall *)&msg->git[i], cx);
	if(msg->called_soft.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLED_SOFT, (union uni_ieall *)&msg->called_soft, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}