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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  trans_seq ;
struct wpa_tdls_ftie {int /*<<< orphan*/  mic; } ;
typedef  int /*<<< orphan*/  rcode ;
typedef  int /*<<< orphan*/  dtoken ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  TDLS_MIC_LEN ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (int*,int /*<<< orphan*/ ) ; 
 int omac1_aes_128 (int const*,int*,int,int*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpa_tdls_key_mic_teardown(const u8 *kck, u8 trans_seq, u16 rcode,
				     u8 dtoken, const u8 *lnkid,
				     const u8 *ftie, u8 *mic)
{
	u8 *buf, *pos;
	struct wpa_tdls_ftie *_ftie;
	int ret;
	int len;

	if (lnkid == NULL)
		return -1;

	len = 2 + lnkid[1] + sizeof(rcode) + sizeof(dtoken) +
		sizeof(trans_seq) + 2 + ftie[1];

	buf = os_zalloc(len);
	if (!buf) {
		wpa_printf(MSG_WARNING, "TDLS: No memory for MIC calculation");
		return -1;
	}

	pos = buf;
	/* 1) Link Identifier IE */
	os_memcpy(pos, lnkid, 2 + lnkid[1]);
	pos += 2 + lnkid[1];
	/* 2) Reason Code */
	WPA_PUT_LE16(pos, rcode);
	pos += sizeof(rcode);
	/* 3) Dialog token */
	*pos++ = dtoken;
	/* 4) Transaction Sequence number */
	*pos++ = trans_seq;
	/* 7) FTIE, with the MIC field of the FTIE set to 0 */
	os_memcpy(pos, ftie, 2 + ftie[1]);
	_ftie = (struct wpa_tdls_ftie *) pos;
	os_memset(_ftie->mic, 0, TDLS_MIC_LEN);
	pos += 2 + ftie[1];

	wpa_hexdump(MSG_DEBUG, "TDLS: Data for FTIE MIC", buf, pos - buf);
	wpa_hexdump_key(MSG_DEBUG, "TDLS: KCK", kck, 16);
	ret = omac1_aes_128(kck, buf, pos - buf, mic);
	os_free(buf);
	wpa_hexdump(MSG_DEBUG, "TDLS: FTIE MIC", mic, 16);
	return ret;
}