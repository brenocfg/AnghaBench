#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
struct unicx {int dummy; } ;
struct TYPE_7__ {int present; } ;
struct TYPE_8__ {TYPE_1__ h; } ;
struct TYPE_11__ {int present; } ;
struct TYPE_12__ {TYPE_5__ h; } ;
struct TYPE_9__ {int present; } ;
struct TYPE_10__ {TYPE_3__ h; } ;
struct uni_notify {TYPE_2__ unrec; TYPE_6__ epref; TYPE_4__ notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_EPREF ; 
 int /*<<< orphan*/  UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_notify(struct uni_notify *msg, struct unicx *cx)
{
	if(msg->notify.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_NOTIFY, (union uni_ieall *)&msg->notify, cx);
	if(msg->epref.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_EPREF, (union uni_ieall *)&msg->epref, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}