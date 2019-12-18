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
struct crypto_tfm {int dummy; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_ablkcipher (struct crypto_ablkcipher*) ; 
 struct crypto_ablkcipher** crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static void crypto_exit_skcipher_ops_ablkcipher(struct crypto_tfm *tfm)
{
	struct crypto_ablkcipher **ctx = crypto_tfm_ctx(tfm);

	crypto_free_ablkcipher(*ctx);
}