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
typedef  int u32 ;
struct ix_sa_dir {int npe_ctx_idx; int /*<<< orphan*/  npe_mode; int /*<<< orphan*/ * npe_ctx; } ;
struct ixp_ctx {struct ix_sa_dir decrypt; struct ix_sa_dir encrypt; } ;
struct crypto_tfm {int crt_flags; } ;
typedef  int /*<<< orphan*/  cipher_cfg ;

/* Variables and functions */
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int DES3_EDE_KEY_SIZE ; 
 int EINVAL ; 
 int MOD_AES ; 
 int MOD_AES128 ; 
 int MOD_AES192 ; 
 int MOD_AES256 ; 
 int /*<<< orphan*/  NPE_OP_CRYPT_ENABLE ; 
 int /*<<< orphan*/  NPE_OP_CRYPT_ENCRYPT ; 
 int cipher_cfg_dec (struct crypto_tfm*) ; 
 int cipher_cfg_enc (struct crypto_tfm*) ; 
 int cpu_to_be32 (int) ; 
 int /*<<< orphan*/  crypto_des_verify_key (struct crypto_tfm*,int /*<<< orphan*/  const*) ; 
 struct ixp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int gen_rev_aes_key (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int setup_cipher(struct crypto_tfm *tfm, int encrypt,
		const u8 *key, int key_len)
{
	u8 *cinfo;
	u32 cipher_cfg;
	u32 keylen_cfg = 0;
	struct ix_sa_dir *dir;
	struct ixp_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;

	dir = encrypt ? &ctx->encrypt : &ctx->decrypt;
	cinfo = dir->npe_ctx;

	if (encrypt) {
		cipher_cfg = cipher_cfg_enc(tfm);
		dir->npe_mode |= NPE_OP_CRYPT_ENCRYPT;
	} else {
		cipher_cfg = cipher_cfg_dec(tfm);
	}
	if (cipher_cfg & MOD_AES) {
		switch (key_len) {
		case 16: keylen_cfg = MOD_AES128; break;
		case 24: keylen_cfg = MOD_AES192; break;
		case 32: keylen_cfg = MOD_AES256; break;
		default:
			*flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
			return -EINVAL;
		}
		cipher_cfg |= keylen_cfg;
	} else {
		crypto_des_verify_key(tfm, key);
	}
	/* write cfg word to cryptinfo */
	*(u32*)cinfo = cpu_to_be32(cipher_cfg);
	cinfo += sizeof(cipher_cfg);

	/* write cipher key to cryptinfo */
	memcpy(cinfo, key, key_len);
	/* NPE wants keylen set to DES3_EDE_KEY_SIZE even for single DES */
	if (key_len < DES3_EDE_KEY_SIZE && !(cipher_cfg & MOD_AES)) {
		memset(cinfo + key_len, 0, DES3_EDE_KEY_SIZE -key_len);
		key_len = DES3_EDE_KEY_SIZE;
	}
	dir->npe_ctx_idx = sizeof(cipher_cfg) + key_len;
	dir->npe_mode |= NPE_OP_CRYPT_ENABLE;
	if ((cipher_cfg & MOD_AES) && !encrypt) {
		return gen_rev_aes_key(tfm);
	}
	return 0;
}