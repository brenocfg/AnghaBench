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
typedef  int uint32_t ;
struct tpm_key {void* blob; int blob_len; int key_len; int pub_key_len; void const* pub_key; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int get_unaligned_be16 (void const*) ; 
 int get_unaligned_be32 (void const*) ; 

__attribute__((used)) static int extract_key_parameters(struct tpm_key *tk)
{
	const void *cur = tk->blob;
	uint32_t len = tk->blob_len;
	const void *pub_key;
	uint32_t sz;
	uint32_t key_len;

	if (len < 11)
		return -EBADMSG;

	/* Ensure this is a legacy key */
	if (get_unaligned_be16(cur + 4) != 0x0015)
		return -EBADMSG;

	/* Skip to TPM_KEY_PARMS */
	cur += 11;
	len -= 11;

	if (len < 12)
		return -EBADMSG;

	/* Make sure this is an RSA key */
	if (get_unaligned_be32(cur) != 0x00000001)
		return -EBADMSG;

	/* Make sure this is TPM_ES_RSAESPKCSv15 encoding scheme */
	if (get_unaligned_be16(cur + 4) != 0x0002)
		return -EBADMSG;

	/* Make sure this is TPM_SS_RSASSAPKCS1v15_DER signature scheme */
	if (get_unaligned_be16(cur + 6) != 0x0003)
		return -EBADMSG;

	sz = get_unaligned_be32(cur + 8);
	if (len < sz + 12)
		return -EBADMSG;

	/* Move to TPM_RSA_KEY_PARMS */
	len -= 12;
	cur += 12;

	/* Grab the RSA key length */
	key_len = get_unaligned_be32(cur);

	switch (key_len) {
	case 512:
	case 1024:
	case 1536:
	case 2048:
		break;
	default:
		return -EINVAL;
	}

	/* Move just past TPM_KEY_PARMS */
	cur += sz;
	len -= sz;

	if (len < 4)
		return -EBADMSG;

	sz = get_unaligned_be32(cur);
	if (len < 4 + sz)
		return -EBADMSG;

	/* Move to TPM_STORE_PUBKEY */
	cur += 4 + sz;
	len -= 4 + sz;

	/* Grab the size of the public key, it should jive with the key size */
	sz = get_unaligned_be32(cur);
	if (sz > 256)
		return -EINVAL;

	pub_key = cur + 4;

	tk->key_len = key_len;
	tk->pub_key = pub_key;
	tk->pub_key_len = sz;

	return 0;
}