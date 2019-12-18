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
struct s390_des_ctx {int /*<<< orphan*/  key; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int crypto_des_verify_key (struct crypto_tfm*,int /*<<< orphan*/  const*) ; 
 struct s390_des_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int des_setkey(struct crypto_tfm *tfm, const u8 *key,
		      unsigned int key_len)
{
	struct s390_des_ctx *ctx = crypto_tfm_ctx(tfm);
	int err;

	err = crypto_des_verify_key(tfm, key);
	if (err)
		return err;

	memcpy(ctx->key, key, key_len);
	return 0;
}