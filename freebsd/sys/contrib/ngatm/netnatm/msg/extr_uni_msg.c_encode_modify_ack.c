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
typedef  size_t u_int ;
struct unicx {int dummy; } ;
struct uni_msg {size_t* b_buf; size_t b_wptr; size_t b_rptr; } ;
struct TYPE_20__ {int present; } ;
struct TYPE_11__ {TYPE_9__ h; } ;
struct TYPE_16__ {int present; } ;
struct TYPE_17__ {TYPE_5__ h; } ;
struct TYPE_14__ {int present; } ;
struct TYPE_15__ {TYPE_3__ h; } ;
struct TYPE_12__ {int present; } ;
struct TYPE_13__ {TYPE_1__ h; } ;
struct uni_modify_ack {TYPE_10__ unrec; TYPE_8__* git; TYPE_6__ notify; TYPE_4__ traffic; TYPE_2__ report; int /*<<< orphan*/  hdr; } ;
struct TYPE_18__ {int present; } ;
struct TYPE_19__ {TYPE_7__ h; } ;

/* Variables and functions */
 int UNI_IE_GIT ; 
 int UNI_IE_NOTIFY ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_REPORT ; 
 int UNI_IE_TRAFFIC ; 
 int UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_MODIFY_ACK ; 
 size_t UNI_NUM_IE_GIT ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,size_t*) ; 

__attribute__((used)) static int
encode_modify_ack(struct uni_msg *msg, struct uni_modify_ack *p, struct unicx *cx)
{
	u_int mlen;
	u_int i;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_MODIFY_ACK, cx, &mlen))
		return (-2);

	if((p->report.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_REPORT, msg, (union uni_ieall *)&p->report, cx))
		return (UNI_IE_REPORT);
	if((p->traffic.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_TRAFFIC, msg, (union uni_ieall *)&p->traffic, cx))
		return (UNI_IE_TRAFFIC);
	if((p->notify.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_NOTIFY, msg, (union uni_ieall *)&p->notify, cx))
		return (UNI_IE_NOTIFY);
	for(i = 0; i < UNI_NUM_IE_GIT; i++)
		if((p->git[i].h.present & UNI_IE_PRESENT) &&
		   uni_encode_ie(UNI_IE_GIT, msg, (union uni_ieall *)&p->git[i], cx))
		return ((i << 16) + UNI_IE_GIT);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}