#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union uni_ieall {int dummy; } uni_ieall ;
typedef  int u_int ;
struct unicx {int dummy; } ;
struct uni_msg {int* b_buf; int b_wptr; int b_rptr; } ;
struct TYPE_15__ {int present; } ;
struct TYPE_16__ {TYPE_7__ h; } ;
struct TYPE_13__ {int present; } ;
struct TYPE_14__ {TYPE_5__ h; } ;
struct TYPE_11__ {int present; } ;
struct TYPE_12__ {TYPE_3__ h; } ;
struct TYPE_9__ {int present; } ;
struct TYPE_10__ {TYPE_1__ h; } ;
struct uni_call_proc {TYPE_8__ unrec; TYPE_6__ notify; TYPE_4__ epref; TYPE_2__ connid; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNI_CALL_PROC ; 
 int UNI_IE_CONNID ; 
 int UNI_IE_EPREF ; 
 int UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_UNREC ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,int*) ; 

__attribute__((used)) static int
encode_call_proc(struct uni_msg *msg, struct uni_call_proc *p, struct unicx *cx)
{
	u_int mlen;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_CALL_PROC, cx, &mlen))
		return (-2);

	if((p->connid.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CONNID, msg, (union uni_ieall *)&p->connid, cx))
		return (UNI_IE_CONNID);
	if((p->epref.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_EPREF, msg, (union uni_ieall *)&p->epref, cx))
		return (UNI_IE_EPREF);
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