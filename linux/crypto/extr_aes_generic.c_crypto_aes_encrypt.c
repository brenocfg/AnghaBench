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
struct crypto_tfm {int dummy; } ;
struct crypto_aes_ctx {int* key_enc; int key_length; } ;

/* Variables and functions */
 struct crypto_aes_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  f_lround (int*,int*,int const*) ; 
 int /*<<< orphan*/  f_nround (int*,int*,int const*) ; 
 int get_unaligned_le32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypto_aes_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in)
{
	const struct crypto_aes_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 b0[4], b1[4];
	const u32 *kp = ctx->key_enc + 4;
	const int key_len = ctx->key_length;

	b0[0] = ctx->key_enc[0] ^ get_unaligned_le32(in);
	b0[1] = ctx->key_enc[1] ^ get_unaligned_le32(in + 4);
	b0[2] = ctx->key_enc[2] ^ get_unaligned_le32(in + 8);
	b0[3] = ctx->key_enc[3] ^ get_unaligned_le32(in + 12);

	if (key_len > 24) {
		f_nround(b1, b0, kp);
		f_nround(b0, b1, kp);
	}

	if (key_len > 16) {
		f_nround(b1, b0, kp);
		f_nround(b0, b1, kp);
	}

	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_nround(b0, b1, kp);
	f_nround(b1, b0, kp);
	f_lround(b0, b1, kp);

	put_unaligned_le32(b0[0], out);
	put_unaligned_le32(b0[1], out + 4);
	put_unaligned_le32(b0[2], out + 8);
	put_unaligned_le32(b0[3], out + 12);
}