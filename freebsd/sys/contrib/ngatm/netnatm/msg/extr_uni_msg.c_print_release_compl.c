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
typedef  int u_int ;
struct unicx {int dummy; } ;
struct TYPE_20__ {int present; } ;
struct TYPE_11__ {TYPE_9__ h; } ;
struct TYPE_18__ {int present; } ;
struct TYPE_19__ {TYPE_7__ h; } ;
struct TYPE_16__ {int present; } ;
struct TYPE_17__ {TYPE_5__ h; } ;
struct uni_release_compl {TYPE_10__ unrec; TYPE_8__ crankback; TYPE_6__ uu; TYPE_4__* git; TYPE_2__* cause; } ;
struct TYPE_14__ {int present; } ;
struct TYPE_15__ {TYPE_3__ h; } ;
struct TYPE_12__ {int present; } ;
struct TYPE_13__ {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_IE_CAUSE ; 
 int /*<<< orphan*/  UNI_IE_CRANKBACK ; 
 int /*<<< orphan*/  UNI_IE_GIT ; 
 int UNI_IE_PRESENT ; 
 int /*<<< orphan*/  UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_IE_UU ; 
 int UNI_NUM_IE_GIT ; 
 int /*<<< orphan*/  uni_print_ie_internal (int /*<<< orphan*/ ,union uni_ieall*,struct unicx*) ; 

__attribute__((used)) static void
print_release_compl(struct uni_release_compl *msg, struct unicx *cx)
{
	u_int i;

	for(i = 0; i < 2; i++)
		if(msg->cause[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_CAUSE, (union uni_ieall *)&msg->cause[i], cx);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if(msg->git[i].h.present & UNI_IE_PRESENT)
			uni_print_ie_internal(UNI_IE_GIT, (union uni_ieall *)&msg->git[i], cx);
	if(msg->uu.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UU, (union uni_ieall *)&msg->uu, cx);
	if(msg->crankback.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_CRANKBACK, (union uni_ieall *)&msg->crankback, cx);
	if(msg->unrec.h.present & UNI_IE_PRESENT)
		uni_print_ie_internal(UNI_IE_UNREC, (union uni_ieall *)&msg->unrec, cx);
}