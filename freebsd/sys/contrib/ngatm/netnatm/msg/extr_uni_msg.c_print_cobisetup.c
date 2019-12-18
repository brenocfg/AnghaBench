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
struct unicx {int dummy; } ;
struct TYPE_14__ {int present; } ;
struct TYPE_15__ {TYPE_11__ h; } ;
struct TYPE_24__ {int present; } ;
struct TYPE_13__ {TYPE_9__ h; } ;
struct TYPE_22__ {int present; } ;
struct TYPE_23__ {TYPE_7__ h; } ;
struct TYPE_20__ {int present; } ;
struct TYPE_21__ {TYPE_5__ h; } ;
struct TYPE_18__ {int present; } ;
struct TYPE_19__ {TYPE_3__ h; } ;
struct TYPE_16__ {int present; } ;
struct TYPE_17__ {TYPE_1__ h; } ;
struct uni_cobisetup {TYPE_12__ unrec; TYPE_10__ notify; TYPE_8__ calling; TYPE_6__ calledsub; TYPE_4__ called; TYPE_2__ facility; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CALLED ; 
 int /*<<< orphan*/  UNI_IE_CALLEDSUB ; 
 int /*<<< orphan*/  UNI_IE_CALLING ; 
 int /*<<< orphan*/  UNI_IE_FACILITY ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_cobisetup(struct uni_cobisetup *msg, struct unicx *cx)
{
	if(msg->facility.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_FACILITY, (union uni_ieall *)&msg->facility, cx);
	if(msg->called.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLED, (union uni_ieall *)&msg->called, cx);
	if(msg->calledsub.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLEDSUB, (union uni_ieall *)&msg->calledsub, cx);
	if(msg->calling.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CALLING, (union uni_ieall *)&msg->calling, cx);
	if(msg->notify.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_NOTIFY, (union uni_ieall *)&msg->notify, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}