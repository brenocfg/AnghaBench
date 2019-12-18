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
struct uni_leaf_setup_req {TYPE_16__ unrec; TYPE_14__ lij_seqno; TYPE_12__ lij_callid; TYPE_10__* calledsub; TYPE_8__ called; TYPE_6__* callingsub; TYPE_4__ calling; TYPE_2__* tns; } ;
struct TYPE_32__ {int present; } ;
struct TYPE_28__ {int present; } ;
struct TYPE_29__ {TYPE_5__ h; } ;
struct TYPE_24__ {int present; } ;
struct TYPE_25__ {TYPE_1__ h; } ;
struct TYPE_17__ {TYPE_9__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CALLED ; 
 int /*<<< orphan*/  UNI_IE_CALLEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CALLING ; 
 int /*<<< orphan*/  UNI_IE_CALLINGSUB ; 
 int /*<<< orphan*/  UNI_IE_LIJ_CALLID ; 
 int /*<<< orphan*/  UNI_IE_LIJ_SEQNO ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_TNS ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 size_t UNI_NUM_IE_CALLEDSUB ; 
 size_t UNI_NUM_IE_CALLINGSUB ; 
 size_t UNI_NUM_IE_TNS ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_leaf_setup_req(struct uni_leaf_setup_req *msg, struct unicx *cx)
{
	u_int i;

	for(i = 0; i < UNI_NUM_IE_TNS; i++)
		if(msg->tns[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_TNS, (union uni_ieall *)&msg->tns[i], cx);
	if(msg->calling.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLING, (union uni_ieall *)&msg->calling, cx);
	for(i = 0; i < UNI_NUM_IE_CALLINGSUB; i++)
		if(msg->callingsub[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_CALLINGSUB, (union uni_ieall *)&msg->callingsub[i], cx);
	if(msg->called.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLED, (union uni_ieall *)&msg->called, cx);
	for(i = 0; i < UNI_NUM_IE_CALLEDSUB; i++)
		if(msg->calledsub[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_CALLEDSUB, (union uni_ieall *)&msg->calledsub[i], cx);
	if(msg->lij_callid.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_LIJ_CALLID, (union uni_ieall *)&msg->lij_callid, cx);
	if(msg->lij_seqno.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_LIJ_SEQNO, (union uni_ieall *)&msg->lij_seqno, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}