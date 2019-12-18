#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  int u_int ;
struct unicx {int dummy; } ;
struct TYPE_18__ {int present; } ;
struct TYPE_19__ {TYPE_13__ h; } ;
struct TYPE_16__ {int present; } ;
struct TYPE_17__ {TYPE_11__ h; } ;
struct TYPE_28__ {int present; } ;
struct TYPE_15__ {TYPE_9__ h; } ;
struct TYPE_26__ {int present; } ;
struct TYPE_27__ {TYPE_7__ h; } ;
struct TYPE_22__ {int present; } ;
struct TYPE_23__ {TYPE_3__ h; } ;
struct uni_release {TYPE_14__ unrec; TYPE_12__ crankback; TYPE_10__ facility; TYPE_8__ uu; TYPE_6__* git; TYPE_4__ notify; TYPE_2__* cause; } ;
struct TYPE_24__ {int present; } ;
struct TYPE_25__ {TYPE_5__ h; } ;
struct TYPE_20__ {int present; } ;
struct TYPE_21__ {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CAUSE ; 
 int /*<<< orphan*/  UNI_IE_CRANKBACK ; 
 int /*<<< orphan*/  UNI_IE_FACILITY ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 int UNI_NUM_IE_GIT ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_release(struct uni_release *msg, struct unicx *cx)
{
	u_int i;

	for(i = 0; i < 2; i++)
		if(msg->cause[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_CAUSE, (union uni_ieall *)&msg->cause[i], cx);
	if(msg->notify.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_NOTIFY, (union uni_ieall *)&msg->notify, cx);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if(msg->git[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_GIT, (union uni_ieall *)&msg->git[i], cx);
	if(msg->uu.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UU, (union uni_ieall *)&msg->uu, cx);
	if(msg->facility.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_FACILITY, (union uni_ieall *)&msg->facility, cx);
	if(msg->crankback.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CRANKBACK, (union uni_ieall *)&msg->crankback, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}