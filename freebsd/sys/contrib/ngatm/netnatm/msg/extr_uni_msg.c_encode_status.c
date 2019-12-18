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
struct TYPE_14__ {int present; } ;
struct TYPE_15__ {TYPE_3__ h; } ;
struct TYPE_12__ {int present; } ;
struct TYPE_13__ {TYPE_1__ h; } ;
struct uni_status {TYPE_10__ unrec; TYPE_8__ epstate; TYPE_6__ epref; TYPE_4__ cause; TYPE_2__ callstate; int /*<<< orphan*/  hdr; } ;
struct uni_msg {int* b_buf; int b_wptr; int b_rptr; } ;

/* Variables and functions */
 int UNI_IE_CALLSTATE ; 
 int UNI_IE_CAUSE ; 
 int UNI_IE_EPREF ; 
 int UNI_IE_EPSTATE ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_STATUS ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,int*) ; 

__attribute__((used)) static int
encode_status(struct uni_msg *msg, struct uni_status *p, struct unicx *cx)
{
	u_int mlen;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_STATUS, cx, &mlen))
		return (-2);

	if((p->callstate.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CALLSTATE, msg, (union uni_ieall *)&p->callstate, cx))
		return (UNI_IE_CALLSTATE);
	if((p->cause.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CAUSE, msg, (union uni_ieall *)&p->cause, cx))
		return (UNI_IE_CAUSE);
	if((p->epref.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EPREF, msg, (union uni_ieall *)&p->epref, cx))
		return (UNI_IE_EPREF);
	if((p->epstate.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EPSTATE, msg, (union uni_ieall *)&p->epstate, cx))
		return (UNI_IE_EPSTATE);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}