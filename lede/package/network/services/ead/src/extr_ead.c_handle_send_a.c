#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ead_msg {int /*<<< orphan*/  len; } ;
struct ead_packet {struct ead_msg msg; } ;
struct ead_msg_number {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {struct ead_msg msg; } ;

/* Variables and functions */
 TYPE_3__ A ; 
 TYPE_2__* B ; 
 struct ead_msg_number* EAD_DATA (struct ead_msg*,struct ead_msg_number*) ; 
 int EAD_TYPE_SEND_AUTH ; 
 int MAXPARAMLEN ; 
 int /*<<< orphan*/  abuf ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 struct ead_msg_number* number ; 
 TYPE_1__* pktbuf ; 

__attribute__((used)) static bool
handle_send_a(struct ead_packet *pkt, int len, int *nstate)
{
	struct ead_msg *msg = &pkt->msg;
	struct ead_msg_number *number = EAD_DATA(msg, number);
	len = ntohl(msg->len) - sizeof(struct ead_msg_number);

	if (len > MAXPARAMLEN + 1)
		return false;

	A.len = len;
	A.data = abuf;
	memcpy(A.data, number->data, len);

	msg = &pktbuf->msg;
	number = EAD_DATA(msg, number);
	msg->len = htonl(sizeof(struct ead_msg_number) + B->len);
	memcpy(number->data, B->data, B->len);

	*nstate = EAD_TYPE_SEND_AUTH;
	return true;
}