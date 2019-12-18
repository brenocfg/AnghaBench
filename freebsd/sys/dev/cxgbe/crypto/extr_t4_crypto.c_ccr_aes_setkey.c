#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int key_len; int /*<<< orphan*/  key_ctx_hdr; int /*<<< orphan*/  deckey; int /*<<< orphan*/  enckey; } ;
struct TYPE_3__ {unsigned int mk_size; int partial_digest_len; } ;
struct ccr_session {int mode; TYPE_2__ blkcipher; TYPE_1__ hmac; } ;
struct _key_ctx {int dummy; } ;

/* Variables and functions */
#define  AUTHENC 132 
#define  CCM 131 
 unsigned int CHCR_KEYCTX_CIPHER_KEY_SIZE_128 ; 
 unsigned int CHCR_KEYCTX_CIPHER_KEY_SIZE_192 ; 
 unsigned int CHCR_KEYCTX_CIPHER_KEY_SIZE_256 ; 
 unsigned int CHCR_KEYCTX_MAC_KEY_SIZE_128 ; 
 unsigned int CHCR_KEYCTX_MAC_KEY_SIZE_192 ; 
 unsigned int CHCR_KEYCTX_MAC_KEY_SIZE_256 ; 
 unsigned int CHCR_KEYCTX_NO_KEY ; 
#define  CRYPTO_AES_CBC 130 
#define  CRYPTO_AES_XTS 129 
#define  GCM 128 
 unsigned int GMAC_BLOCK_LEN ; 
 int V_KEY_CONTEXT_CK_SIZE (unsigned int) ; 
 int V_KEY_CONTEXT_CTX_LEN (unsigned int) ; 
 int V_KEY_CONTEXT_DUAL_CK (int) ; 
 int V_KEY_CONTEXT_MK_SIZE (unsigned int) ; 
 int V_KEY_CONTEXT_OPAD_PRESENT (unsigned int) ; 
 int V_KEY_CONTEXT_SALT_PRESENT (int) ; 
 int V_KEY_CONTEXT_VALID (int) ; 
 int /*<<< orphan*/  htobe32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 unsigned int roundup2 (int,int) ; 
 int /*<<< orphan*/  t4_aes_getdeckey (int /*<<< orphan*/ ,void const*,unsigned int) ; 

__attribute__((used)) static void
ccr_aes_setkey(struct ccr_session *s, int alg, const void *key, int klen)
{
	unsigned int ck_size, iopad_size, kctx_flits, kctx_len, kbits, mk_size;
	unsigned int opad_present;

	if (alg == CRYPTO_AES_XTS)
		kbits = klen / 2;
	else
		kbits = klen;
	switch (kbits) {
	case 128:
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_128;
		break;
	case 192:
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_192;
		break;
	case 256:
		ck_size = CHCR_KEYCTX_CIPHER_KEY_SIZE_256;
		break;
	default:
		panic("should not get here");
	}

	s->blkcipher.key_len = klen / 8;
	memcpy(s->blkcipher.enckey, key, s->blkcipher.key_len);
	switch (alg) {
	case CRYPTO_AES_CBC:
	case CRYPTO_AES_XTS:
		t4_aes_getdeckey(s->blkcipher.deckey, key, kbits);
		break;
	}

	kctx_len = roundup2(s->blkcipher.key_len, 16);
	switch (s->mode) {
	case AUTHENC:
		mk_size = s->hmac.mk_size;
		opad_present = 1;
		iopad_size = roundup2(s->hmac.partial_digest_len, 16);
		kctx_len += iopad_size * 2;
		break;
	case GCM:
		mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_128;
		opad_present = 0;
		kctx_len += GMAC_BLOCK_LEN;
		break;
	case CCM:
		switch (kbits) {
		case 128:
			mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_128;
			break;
		case 192:
			mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_192;
			break;
		case 256:
			mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
			break;
		default:
			panic("should not get here");
		}
		opad_present = 0;
		kctx_len *= 2;
		break;
	default:
		mk_size = CHCR_KEYCTX_NO_KEY;
		opad_present = 0;
		break;
	}
	kctx_flits = (sizeof(struct _key_ctx) + kctx_len) / 16;
	s->blkcipher.key_ctx_hdr = htobe32(V_KEY_CONTEXT_CTX_LEN(kctx_flits) |
	    V_KEY_CONTEXT_DUAL_CK(alg == CRYPTO_AES_XTS) |
	    V_KEY_CONTEXT_OPAD_PRESENT(opad_present) |
	    V_KEY_CONTEXT_SALT_PRESENT(1) | V_KEY_CONTEXT_CK_SIZE(ck_size) |
	    V_KEY_CONTEXT_MK_SIZE(mk_size) | V_KEY_CONTEXT_VALID(1));
}