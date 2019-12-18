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
typedef  long uLong ;
struct params {char* packet; char* ap; char* mac; char* iv; int prga_len; char* prga; int packet_len; int /*<<< orphan*/  state; scalar_t__ data_try; int /*<<< orphan*/  seq; int /*<<< orphan*/  tap; } ;
struct ieee80211_frame {int* i_dur; char* i_addr1; char* i_addr2; char* i_addr3; scalar_t__ i_seq; int /*<<< orphan*/ * i_fc; } ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC1_DIR_TODS ; 
 int /*<<< orphan*/  IEEE80211_FC1_PROTECTED ; 
 int /*<<< orphan*/  S_WAIT_ACK ; 
 char* Z_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 long crc32 (long,char*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_packet (struct params*) ; 
 short seqfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void read_tap(struct params *p)
{
	int offset;
	char *ptr;
	struct ieee80211_frame *wh;
	int rc;
	char dst[6];
	short *seq;
	uLong *pcrc;
	uLong crc = crc32(0L, Z_NULL, 0);

	memset(p->packet, 0, sizeof(p->packet));
	offset = sizeof(*wh) + 4 + 8 - 14;
	rc = sizeof(p->packet) - offset;
	ptr = &p->packet[offset];

	rc = read(p->tap, ptr, rc);
	if (rc == -1)
		err(1, "read()");

	memcpy(dst, ptr, sizeof(dst));
	wh = (struct ieee80211_frame*) p->packet;
	wh->i_fc[0] |= IEEE80211_FC0_TYPE_DATA;
	wh->i_fc[0] |= IEEE80211_FC0_SUBTYPE_DATA;
	wh->i_fc[1] |= IEEE80211_FC1_PROTECTED;
	wh->i_fc[1] |= IEEE80211_FC1_DIR_TODS;

	wh->i_dur[0] = 0x69;

	memcpy(wh->i_addr1, p->ap, 6);
	memcpy(wh->i_addr2, p->mac, 6);
	memcpy(wh->i_addr3, dst, 6);

	seq = (short*) wh->i_seq;
	*seq = seqfn(p->seq++, 0);

	/* data */
	ptr = (char*) (wh+1);
	memcpy(ptr, p->iv, 3);
	ptr += 3;
	*ptr++ = 0;
	memcpy(ptr, "\xAA\xAA\x03\x00\x00\x00", 6);
	rc -= 14;
	rc += 8;
	
	crc = crc32(crc, ptr, rc);
	pcrc = (uLong*) (ptr+rc);
	*pcrc = crc;

	rc += 4;

	assert(p->prga_len >= rc);

	/* wepify */
	for (offset = 0; offset < rc; offset++)
		ptr[offset] ^= p->prga[offset];

	p->packet_len = sizeof(*wh) + 4 + rc;
	p->data_try = 0;
	send_packet(p);
	p->state = S_WAIT_ACK;
}