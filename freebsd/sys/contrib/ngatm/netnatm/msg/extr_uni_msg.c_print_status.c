#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
struct unicx {int dummy; } ;
struct TYPE_20__ {int present; } ;
struct TYPE_11__ {TYPE_9__ h; } ;
struct TYPE_18__ {int present; } ;
struct TYPE_19__ {TYPE_7__ h; } ;
struct TYPE_16__ {int present; } ;
struct TYPE_17__ {TYPE_5__ h; } ;
struct TYPE_14__ {int present; } ;
struct TYPE_15__ {TYPE_3__ h; } ;
struct TYPE_12__ {int present; } ;
struct TYPE_13__ {TYPE_1__ h; } ;
struct uni_status {TYPE_10__ unrec; TYPE_8__ epstate; TYPE_6__ epref; TYPE_4__ cause; TYPE_2__ callstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CALLSTATE ; 
 int /*<<< orphan*/  UNI_IE_CAUSE ; 
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_EPSTATE ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_status(struct uni_status *msg, struct unicx *cx)
{
	if(msg->callstate.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLSTATE, (union uni_ieall *)&msg->callstate, cx);
	if(msg->cause.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CAUSE, (union uni_ieall *)&msg->cause, cx);
	if(msg->epref.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EPREF, (union uni_ieall *)&msg->epref, cx);
	if(msg->epstate.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EPSTATE, (union uni_ieall *)&msg->epstate, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}