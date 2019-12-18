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
typedef  int /*<<< orphan*/  const u8 ;
struct TYPE_4__ {size_t used_bytes; int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int /*<<< orphan*/  cbc; TYPE_2__ rc4; } ;
struct crypto_cipher {TYPE_1__ u; scalar_t__ rc4; } ;

/* Variables and functions */
 int CRYPT_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int cbc_decrypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_to_string (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  rc4_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int crypto_cipher_decrypt(struct crypto_cipher *ctx, const u8 *crypt,
			  u8 *plain, size_t len)
{
	int res;

	if (ctx->rc4) {
		if (plain != crypt)
			os_memcpy(plain, crypt, len);
		rc4_skip(ctx->u.rc4.key, ctx->u.rc4.keylen,
			 ctx->u.rc4.used_bytes, plain, len);
		ctx->u.rc4.used_bytes += len;
		return 0;
	}

	res = cbc_decrypt(crypt, plain, len, &ctx->u.cbc);
	if (res != CRYPT_OK) {
		wpa_printf(MSG_DEBUG, "LibTomCrypt: CBC decryption "
			   "failed: %s", error_to_string(res));
		return -1;
	}

	return 0;
}