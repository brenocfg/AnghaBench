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
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  size_t u_int ;
struct unicx {int dummy; } ;
struct TYPE_14__ {int present; } ;
struct TYPE_15__ {TYPE_11__ h; } ;
struct TYPE_22__ {int present; } ;
struct TYPE_23__ {TYPE_7__ h; } ;
struct TYPE_20__ {int present; } ;
struct TYPE_21__ {TYPE_5__ h; } ;
struct TYPE_18__ {int present; } ;
struct TYPE_19__ {TYPE_3__ h; } ;
struct TYPE_16__ {int present; } ;
struct TYPE_17__ {TYPE_1__ h; } ;
struct uni_leaf_setup_fail {TYPE_12__ unrec; TYPE_10__* tns; TYPE_8__ lij_seqno; TYPE_6__ calledsub; TYPE_4__ called; TYPE_2__ cause; } ;
struct TYPE_24__ {int present; } ;
struct TYPE_13__ {TYPE_9__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CALLED ; 
 int /*<<< orphan*/  UNI_IE_CALLEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CAUSE ; 
 int /*<<< orphan*/  UNI_IE_LIJ_SEQNO ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_TNS ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 size_t UNI_NUM_IE_TNS ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_leaf_setup_fail(struct uni_leaf_setup_fail *msg, struct unicx *cx)
{
	u_int i;

	if(msg->cause.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CAUSE, (union uni_ieall *)&msg->cause, cx);
	if(msg->called.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLED, (union uni_ieall *)&msg->called, cx);
	if(msg->calledsub.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLEDSUB, (union uni_ieall *)&msg->calledsub, cx);
	if(msg->lij_seqno.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_LIJ_SEQNO, (union uni_ieall *)&msg->lij_seqno, cx);
	for(i = 0; i < UNI_NUM_IE_TNS; i++)
		if(msg->tns[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_TNS, (union uni_ieall *)&msg->tns[i], cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}