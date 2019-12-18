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
typedef  int u_int ;
struct unicx {int dummy; } ;
struct uni_msg {int* b_buf; int b_wptr; int b_rptr; } ;
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
struct uni_facility {TYPE_12__ unrec; TYPE_10__ notify; TYPE_8__ calling; TYPE_6__ calledsub; TYPE_4__ called; TYPE_2__ facility; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_FACILITY ; 
 int UNI_IE_CALLED ; 
 int UNI_IE_CALLEDSUB ; 
 int UNI_IE_CALLING ; 
 int UNI_IE_FACILITY ; 
 int UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_UNREC ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,int*) ; 

__attribute__((used)) static int
encode_facility(struct uni_msg *msg, struct uni_facility *p, struct unicx *cx)
{
	u_int mlen;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_FACILITY, cx, &mlen))
		return (-2);

	if((p->facility.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_FACILITY, msg, (union uni_ieall *)&p->facility, cx))
		return (UNI_IE_FACILITY);
	if((p->called.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLED, msg, (union uni_ieall *)&p->called, cx))
		return (UNI_IE_CALLED);
	if((p->calledsub.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLEDSUB, msg, (union uni_ieall *)&p->calledsub, cx))
		return (UNI_IE_CALLEDSUB);
	if((p->calling.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLING, msg, (union uni_ieall *)&p->calling, cx))
		return (UNI_IE_CALLING);
	if((p->notify.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_NOTIFY, msg, (union uni_ieall *)&p->notify, cx))
		return (UNI_IE_NOTIFY);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}