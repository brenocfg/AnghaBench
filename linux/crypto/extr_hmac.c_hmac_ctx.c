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
struct hmac_ctx {int dummy; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 struct hmac_ctx* align_ptr (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_shash_ctx_aligned (struct crypto_shash*) ; 
 int crypto_shash_statesize (struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_tfm_ctx_alignment () ; 

__attribute__((used)) static inline struct hmac_ctx *hmac_ctx(struct crypto_shash *tfm)
{
	return align_ptr(crypto_shash_ctx_aligned(tfm) +
			 crypto_shash_statesize(tfm) * 2,
			 crypto_tfm_ctx_alignment());
}