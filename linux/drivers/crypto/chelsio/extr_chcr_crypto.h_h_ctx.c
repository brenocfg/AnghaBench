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
struct crypto_ahash {int dummy; } ;
struct chcr_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct chcr_context* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct chcr_context *h_ctx(struct crypto_ahash *tfm)
{
	return crypto_tfm_ctx(crypto_ahash_tfm(tfm));
}