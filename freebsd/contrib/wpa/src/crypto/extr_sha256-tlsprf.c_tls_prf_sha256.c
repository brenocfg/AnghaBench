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
typedef  unsigned char u8 ;

/* Variables and functions */
 int SHA256_MAC_LEN ; 
 scalar_t__ hmac_sha256 (unsigned char const*,size_t,unsigned char*,int,unsigned char*) ; 
 scalar_t__ hmac_sha256_vector (unsigned char const*,size_t,int,unsigned char const**,size_t*,unsigned char*) ; 
 int /*<<< orphan*/  os_memcpy (unsigned char*,unsigned char*,size_t) ; 
 size_t os_strlen (char const*) ; 

int tls_prf_sha256(const u8 *secret, size_t secret_len, const char *label,
		   const u8 *seed, size_t seed_len, u8 *out, size_t outlen)
{
	size_t clen;
	u8 A[SHA256_MAC_LEN];
	u8 P[SHA256_MAC_LEN];
	size_t pos;
	const unsigned char *addr[3];
	size_t len[3];

	addr[0] = A;
	len[0] = SHA256_MAC_LEN;
	addr[1] = (unsigned char *) label;
	len[1] = os_strlen(label);
	addr[2] = seed;
	len[2] = seed_len;

	/*
	 * RFC 5246, Chapter 5
	 * A(0) = seed, A(i) = HMAC(secret, A(i-1))
	 * P_hash = HMAC(secret, A(1) + seed) + HMAC(secret, A(2) + seed) + ..
	 * PRF(secret, label, seed) = P_SHA256(secret, label + seed)
	 */

	if (hmac_sha256_vector(secret, secret_len, 2, &addr[1], &len[1], A) < 0)
		return -1;

	pos = 0;
	while (pos < outlen) {
		if (hmac_sha256_vector(secret, secret_len, 3, addr, len, P) <
		    0 ||
		    hmac_sha256(secret, secret_len, A, SHA256_MAC_LEN, A) < 0)
			return -1;

		clen = outlen - pos;
		if (clen > SHA256_MAC_LEN)
			clen = SHA256_MAC_LEN;
		os_memcpy(out + pos, P, clen);
		pos += clen;
	}

	return 0;
}