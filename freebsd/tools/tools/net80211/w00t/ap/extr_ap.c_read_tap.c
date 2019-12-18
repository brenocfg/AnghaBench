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
struct params {char wep_iv; int /*<<< orphan*/  wep_len; int /*<<< orphan*/  wep_key; int /*<<< orphan*/  tap; } ;
struct ieee80211_frame {char* i_addr3; char* i_addr1; int /*<<< orphan*/ * i_fc; } ;
typedef  int /*<<< orphan*/  src ;
typedef  int /*<<< orphan*/  dst ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC1_DIR_FROMDS ; 
 int /*<<< orphan*/  IEEE80211_FC1_PROTECTED ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fill_basic (struct ieee80211_frame*,struct params*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  send_frame (struct params*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  wep_encrypt (struct ieee80211_frame*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void read_tap(struct params *p)
{
	char buf[4096];
	char *ptr;
	int len = sizeof(buf);
	int offset;
	char src[6], dst[6];
	struct ieee80211_frame *wh;
	int rd;

	ptr = buf;
	offset = sizeof(struct ieee80211_frame) + 8 - 14;
	if (p->wep_len)
		offset += 4;

	ptr += offset;
	len -= offset;

	/* read packet */
	memset(buf, 0, sizeof(buf));
	rd = read(p->tap, ptr, len);
	if (rd == -1)
		err(1, "read()");

	/* 802.11 header */
	wh = (struct ieee80211_frame*) buf;
	memcpy(dst, ptr, sizeof(dst));
	memcpy(src, ptr+6, sizeof(src));
	fill_basic(wh, p);
	memcpy(wh->i_addr3, src, sizeof(wh->i_addr3));
	memcpy(wh->i_addr1, dst, sizeof(wh->i_addr1));
	wh->i_fc[0] |= IEEE80211_FC0_TYPE_DATA;
	wh->i_fc[1] |= IEEE80211_FC1_DIR_FROMDS;
	if (p->wep_len)
		wh->i_fc[1] |= IEEE80211_FC1_PROTECTED;

	/* LLC & SNAP */
	ptr = (char*) (wh+1);
	if (p->wep_len)
		ptr += 4;
	*ptr++ = 0xAA;
	*ptr++ = 0xAA;
	*ptr++ = 0x03;
	*ptr++ = 0x00;
	*ptr++ = 0x00;
	*ptr++ = 0x00;
	/* ether type overlaps w00t */

	rd += offset;

	/* WEP */
	if (p->wep_len) {
		ptr = (char*) (wh+1);
		memcpy(ptr, &p->wep_iv, 3);
		ptr[3] = 0;
		p->wep_iv++;

		wep_encrypt(wh, rd, p->wep_key, p->wep_len);
		rd += 4; /* ICV */
	}

	send_frame(p, wh, rd);
}