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
typedef  int /*<<< orphan*/  ibuf ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ omac1_aes_128_vector (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int eap_gpsk_gkdf_cmac(const u8 *psk /* Y */,
			      const u8 *data /* Z */, size_t data_len,
			      u8 *buf, size_t len /* X */)
{
	u8 *opos;
	size_t i, n, hashlen, left, clen;
	u8 ibuf[2], hash[16];
	const u8 *addr[2];
	size_t vlen[2];

	hashlen = sizeof(hash);
	/* M_i = MAC_Y (i || Z); (MAC = AES-CMAC-128) */
	addr[0] = ibuf;
	vlen[0] = sizeof(ibuf);
	addr[1] = data;
	vlen[1] = data_len;

	opos = buf;
	left = len;
	n = (len + hashlen - 1) / hashlen;
	for (i = 1; i <= n; i++) {
		WPA_PUT_BE16(ibuf, i);
		if (omac1_aes_128_vector(psk, 2, addr, vlen, hash))
			return -1;
		clen = left > hashlen ? hashlen : left;
		os_memcpy(opos, hash, clen);
		opos += clen;
		left -= clen;
	}

	return 0;
}