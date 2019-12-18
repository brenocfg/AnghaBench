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
typedef  int /*<<< orphan*/  u64 ;
struct des_sparc64_ctx {int /*<<< orphan*/ * decrypt_expkey; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct des_sparc64_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  des_sparc64_crypt (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sparc_des_decrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct des_sparc64_ctx *ctx = crypto_tfm_ctx(tfm);
	const u64 *K = ctx->decrypt_expkey;

	des_sparc64_crypt(K, (const u64 *) src, (u64 *) dst);
}