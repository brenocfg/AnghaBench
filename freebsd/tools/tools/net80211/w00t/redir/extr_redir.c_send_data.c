#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct queue {int len; scalar_t__ wh; } ;
struct params {char* ap; char* mac; char* rtr; int packet_len; scalar_t__ data_try; int /*<<< orphan*/  frag; int /*<<< orphan*/  seq; scalar_t__ packet; struct queue* q; } ;
struct ieee80211_frame {int* i_dur; char* i_addr1; char* i_addr2; char* i_addr3; scalar_t__ i_seq; int /*<<< orphan*/ * i_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC1_DIR_TODS ; 
 int /*<<< orphan*/  IEEE80211_FC1_PROTECTED ; 
 int /*<<< orphan*/  assert (struct queue*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_packet (struct params*) ; 
 short seqfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void send_data(struct params *p)
{
	struct ieee80211_frame *wh;
	short *seq;
	struct queue *q = p->q;
	char *dst, *src;
	int len;

	assert(q);

	/* 802.11 */
	memset(p->packet, 0, sizeof(p->packet));
	wh = (struct ieee80211_frame*) p->packet;
	wh->i_fc[0] |= IEEE80211_FC0_TYPE_DATA;
	wh->i_fc[0] |= IEEE80211_FC0_SUBTYPE_DATA;
	wh->i_fc[1] |= IEEE80211_FC1_DIR_TODS;
	wh->i_fc[1] |= IEEE80211_FC1_PROTECTED;
	
	wh->i_dur[0] = 0x69;
	
	memcpy(wh->i_addr1, p->ap, 6);
	memcpy(wh->i_addr2, p->mac, 6);
	memcpy(wh->i_addr3, p->rtr, 6);

	seq = (short*) wh->i_seq;
	*seq = seqfn(p->seq, p->frag++);

	/* data */
	dst = (char*) (wh+1);
	src = (char*) (q->wh+1);
	len = q->len - sizeof(*wh);
	memcpy(dst, src, len);

	p->packet_len = sizeof(*wh) + len;	
	p->data_try = 0;
	send_packet(p);
}