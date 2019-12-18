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
 int SHA1_MAC_LEN ; 
 int /*<<< orphan*/  add_byte_array_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  inc_byte_array (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (unsigned int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sha1_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pkcs12_key_gen(const u8 *pw, size_t pw_len, const u8 *salt,
			  size_t salt_len, u8 id, unsigned int iter,
			  size_t out_len, u8 *out)
{
	unsigned int u, v, S_len, P_len, i;
	u8 *D = NULL, *I = NULL, *B = NULL, *pos;
	int res = -1;

	/* RFC 7292, B.2 */
	u = SHA1_MAC_LEN;
	v = 64;

	/* D = copies of ID */
	D = os_malloc(v);
	if (!D)
		goto done;
	os_memset(D, id, v);

	/* S = copies of salt; P = copies of password, I = S || P */
	S_len = v * ((salt_len + v - 1) / v);
	P_len = v * ((pw_len + v - 1) / v);
	I = os_malloc(S_len + P_len);
	if (!I)
		goto done;
	pos = I;
	if (salt_len) {
		for (i = 0; i < S_len; i++)
			*pos++ = salt[i % salt_len];
	}
	if (pw_len) {
		for (i = 0; i < P_len; i++)
			*pos++ = pw[i % pw_len];
	}

	B = os_malloc(v);
	if (!B)
		goto done;

	for (;;) {
		u8 hash[SHA1_MAC_LEN];
		const u8 *addr[2];
		size_t len[2];

		addr[0] = D;
		len[0] = v;
		addr[1] = I;
		len[1] = S_len + P_len;
		if (sha1_vector(2, addr, len, hash) < 0)
			goto done;

		addr[0] = hash;
		len[0] = SHA1_MAC_LEN;
		for (i = 1; i < iter; i++) {
			if (sha1_vector(1, addr, len, hash) < 0)
				goto done;
		}

		if (out_len <= u) {
			os_memcpy(out, hash, out_len);
			res = 0;
			goto done;
		}

		os_memcpy(out, hash, u);
		out += u;
		out_len -= u;

		/* I_j = (I_j + B + 1) mod 2^(v*8) */
		/* B = copies of Ai (final hash value) */
		for (i = 0; i < v; i++)
			B[i] = hash[i % u];
		inc_byte_array(B, v);
		for (i = 0; i < S_len + P_len; i += v)
			add_byte_array_mod(&I[i], B, v);
	}

done:
	os_free(B);
	os_free(I);
	os_free(D);
	return res;
}