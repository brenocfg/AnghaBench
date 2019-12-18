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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
struct TYPE_6__ {TYPE_2__* tcp; } ;
struct alias_link {TYPE_3__ data; } ;
struct ack_data_record {int delta; int active; void* ack_new; void* ack_old; } ;
struct TYPE_4__ {int index; } ;
struct TYPE_5__ {TYPE_1__ state; struct ack_data_record* ack; } ;

/* Variables and functions */
 int N_LINK_TCP_DATA ; 
 void* htonl (scalar_t__) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

void
AddSeq(struct alias_link *lnk, int delta, u_int ip_hl, u_short ip_len, 
    u_long th_seq, u_int th_off)
{
/*
When a TCP packet has been altered in length, save this
information in a circular list.  If enough packets have
been altered, then this list will begin to overwrite itself.
*/

	struct ack_data_record x;
	int hlen, tlen, dlen;
	int i;

	hlen = (ip_hl + th_off) << 2;
	tlen = ntohs(ip_len);
	dlen = tlen - hlen;

	x.ack_old = htonl(ntohl(th_seq) + dlen);
	x.ack_new = htonl(ntohl(th_seq) + dlen + delta);
	x.delta = delta;
	x.active = 1;

	i = lnk->data.tcp->state.index;
	lnk->data.tcp->ack[i] = x;

	i++;
	if (i == N_LINK_TCP_DATA)
		lnk->data.tcp->state.index = 0;
	else
		lnk->data.tcp->state.index = i;
}