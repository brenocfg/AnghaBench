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
struct khazad_ctx {int /*<<< orphan*/  E; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct khazad_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  khazad_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void khazad_encrypt(struct crypto_tfm *tfm, u8 *dst, const u8 *src)
{
	struct khazad_ctx *ctx = crypto_tfm_ctx(tfm);
	khazad_crypt(ctx->E, dst, src);
}