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
typedef  int u_int ;
struct unicx {int dummy; } ;
struct TYPE_11__ {int present; } ;
struct TYPE_12__ {TYPE_5__ h; } ;
struct TYPE_9__ {int present; } ;
struct TYPE_10__ {TYPE_3__ h; } ;
struct TYPE_7__ {int present; } ;
struct TYPE_8__ {TYPE_1__ h; } ;
struct uni_restart_ack {TYPE_6__ unrec; TYPE_4__ restart; TYPE_2__ connid; int /*<<< orphan*/  hdr; } ;
struct uni_msg {int* b_buf; int b_wptr; int b_rptr; } ;

/* Variables and functions */
 int UNI_IE_CONNID ; 
 int UNI_IE_PRESENT ; 
 int UNI_IE_RESTART ; 
 int UNI_IE_UNREC ; 
 int /*<<< orphan*/  UNI_RESTART_ACK ; 
 scalar_t__ uni_encode_ie (int,struct uni_msg*,union uni_ieall*,struct unicx*) ; 
 scalar_t__ uni_encode_msg_hdr (struct uni_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct unicx*,int*) ; 

__attribute__((used)) static int
encode_restart_ack(struct uni_msg *msg, struct uni_restart_ack *p, struct unicx *cx)
{
	u_int mlen;

	if(uni_encode_msg_hdr(msg, &p->hdr, UNI_RESTART_ACK, cx, &mlen))
		return (-2);

	if((p->connid.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_CONNID, msg, (union uni_ieall *)&p->connid, cx))
		return (UNI_IE_CONNID);
	if((p->restart.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_RESTART, msg, (union uni_ieall *)&p->restart, cx))
		return (UNI_IE_RESTART);
	if((p->unrec.h.present & UNI_IE_PRESENT) &&
	   uni_encode_ie(UNI_IE_UNREC, msg, (union uni_ieall *)&p->unrec, cx))
		return (UNI_IE_UNREC);

	msg->b_buf[mlen+0] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 8;
	msg->b_buf[mlen+1] = ((msg->b_wptr-msg->b_rptr)-mlen-2) >> 0;

	return (0);
}