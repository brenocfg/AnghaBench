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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SAKE_MIC_LEN ; 
 int EAP_SAKE_RAND_LEN ; 
 int /*<<< orphan*/  EAP_SAKE_TEK_AUTH_LEN ; 
 int eap_sake_kdf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int eap_sake_compute_mic(const u8 *tek_auth,
			 const u8 *rand_s, const u8 *rand_p,
			 const u8 *serverid, size_t serverid_len,
			 const u8 *peerid, size_t peerid_len,
			 int peer, const u8 *eap, size_t eap_len,
			 const u8 *mic_pos, u8 *mic)
{
	u8 _rand[2 * EAP_SAKE_RAND_LEN];
	u8 *tmp, *pos;
	size_t tmplen;
	int ret;

	tmplen = serverid_len + 1 + peerid_len + 1 + eap_len;
	tmp = os_malloc(tmplen);
	if (tmp == NULL)
		return -1;
	pos = tmp;
	if (peer) {
		if (peerid) {
			os_memcpy(pos, peerid, peerid_len);
			pos += peerid_len;
		}
		*pos++ = 0x00;
		if (serverid) {
			os_memcpy(pos, serverid, serverid_len);
			pos += serverid_len;
		}
		*pos++ = 0x00;

		os_memcpy(_rand, rand_s, EAP_SAKE_RAND_LEN);
		os_memcpy(_rand + EAP_SAKE_RAND_LEN, rand_p,
			  EAP_SAKE_RAND_LEN);
	} else {
		if (serverid) {
			os_memcpy(pos, serverid, serverid_len);
			pos += serverid_len;
		}
		*pos++ = 0x00;
		if (peerid) {
			os_memcpy(pos, peerid, peerid_len);
			pos += peerid_len;
		}
		*pos++ = 0x00;

		os_memcpy(_rand, rand_p, EAP_SAKE_RAND_LEN);
		os_memcpy(_rand + EAP_SAKE_RAND_LEN, rand_s,
			  EAP_SAKE_RAND_LEN);
	}

	os_memcpy(pos, eap, eap_len);
	os_memset(pos + (mic_pos - eap), 0, EAP_SAKE_MIC_LEN);

	ret = eap_sake_kdf(tek_auth, EAP_SAKE_TEK_AUTH_LEN,
			   peer ? "Peer MIC" : "Server MIC",
			   _rand, 2 * EAP_SAKE_RAND_LEN, tmp, tmplen,
			   mic, EAP_SAKE_MIC_LEN);

	os_free(tmp);

	return ret;
}