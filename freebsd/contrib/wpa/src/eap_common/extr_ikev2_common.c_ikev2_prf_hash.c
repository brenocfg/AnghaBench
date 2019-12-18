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
#define  PRF_HMAC_MD5 129 
#define  PRF_HMAC_SHA1 128 
 int hmac_md5_vector (int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ *) ; 
 int hmac_sha1_vector (int /*<<< orphan*/  const*,size_t,size_t,int /*<<< orphan*/  const**,size_t const*,int /*<<< orphan*/ *) ; 

int ikev2_prf_hash(int alg, const u8 *key, size_t key_len,
		   size_t num_elem, const u8 *addr[], const size_t *len,
		   u8 *hash)
{
	switch (alg) {
	case PRF_HMAC_SHA1:
		return hmac_sha1_vector(key, key_len, num_elem, addr, len,
					hash);
	case PRF_HMAC_MD5:
		return hmac_md5_vector(key, key_len, num_elem, addr, len, hash);
	default:
		return -1;
	}
}