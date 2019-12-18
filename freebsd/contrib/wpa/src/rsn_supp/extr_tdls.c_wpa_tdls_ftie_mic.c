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
struct wpa_tdls_lnkid {int const* init_sta; int const* resp_sta; } ;
struct wpa_tdls_ftie {int /*<<< orphan*/  mic; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  TDLS_MIC_LEN ; 
 int omac1_aes_128 (int const*,int*,int,int*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int /*<<< orphan*/  os_memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* os_zalloc (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wpa_tdls_ftie_mic(const u8 *kck, u8 trans_seq, const u8 *lnkid,
			     const u8 *rsnie, const u8 *timeoutie,
			     const u8 *ftie, u8 *mic)
{
	u8 *buf, *pos;
	struct wpa_tdls_ftie *_ftie;
	const struct wpa_tdls_lnkid *_lnkid;
	int ret;
	int len = 2 * ETH_ALEN + 1 + 2 + lnkid[1] + 2 + rsnie[1] +
		2 + timeoutie[1] + 2 + ftie[1];
	buf = os_zalloc(len);
	if (!buf) {
		wpa_printf(MSG_WARNING, "TDLS: No memory for MIC calculation");
		return -1;
	}

	pos = buf;
	_lnkid = (const struct wpa_tdls_lnkid *) lnkid;
	/* 1) TDLS initiator STA MAC address */
	os_memcpy(pos, _lnkid->init_sta, ETH_ALEN);
	pos += ETH_ALEN;
	/* 2) TDLS responder STA MAC address */
	os_memcpy(pos, _lnkid->resp_sta, ETH_ALEN);
	pos += ETH_ALEN;
	/* 3) Transaction Sequence number */
	*pos++ = trans_seq;
	/* 4) Link Identifier IE */
	os_memcpy(pos, lnkid, 2 + lnkid[1]);
	pos += 2 + lnkid[1];
	/* 5) RSN IE */
	os_memcpy(pos, rsnie, 2 + rsnie[1]);
	pos += 2 + rsnie[1];
	/* 6) Timeout Interval IE */
	os_memcpy(pos, timeoutie, 2 + timeoutie[1]);
	pos += 2 + timeoutie[1];
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