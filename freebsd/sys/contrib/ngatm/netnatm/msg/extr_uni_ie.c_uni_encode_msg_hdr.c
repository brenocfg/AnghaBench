#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct unicx {scalar_t__ pnni; } ;
struct TYPE_2__ {int cref; scalar_t__ flag; } ;
struct uni_msghdr {int act; scalar_t__ pass; TYPE_1__ cref; } ;
struct uni_msg {int b_wptr; int b_rptr; } ;
typedef  enum uni_msgtype { ____Placeholder_uni_msgtype } uni_msgtype ;

/* Variables and functions */
 int /*<<< orphan*/  APP_16BIT (struct uni_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APP_24BIT (struct uni_msg*,int) ; 
 int /*<<< orphan*/  APP_BYTE (struct uni_msg*,int) ; 
 int PNNI_PROTO ; 
 int UNI_MSGACT_DEFAULT ; 
 int UNI_PROTO ; 
 int /*<<< orphan*/  uni_msg_ensure (struct uni_msg*,int) ; 

int
uni_encode_msg_hdr(struct uni_msg *msg, struct uni_msghdr *h,
    enum uni_msgtype type, struct unicx *cx, int *mlen)
{
	u_char byte;

	(void)uni_msg_ensure(msg, 9);

	APP_BYTE(msg, cx->pnni ? PNNI_PROTO : UNI_PROTO); 
	APP_BYTE(msg, 3); 
	if(h->cref.cref >= 1<<23) 
		return -1; 
	APP_24BIT(msg, h->cref.cref | (h->cref.flag ? 0x800000 : 0));
	APP_BYTE(msg, type); 

	byte = 0x80;
	if(h->act != UNI_MSGACT_DEFAULT)
		byte |= 0x10 | (h->act & 3);
	if(cx->pnni && h->pass)
		byte |= 0x08;
	APP_BYTE(msg, byte); 

	*mlen = msg->b_wptr - msg->b_rptr; 
	APP_16BIT(msg, 0);

	return 0;
}