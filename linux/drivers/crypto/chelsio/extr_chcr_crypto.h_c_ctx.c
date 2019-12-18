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
struct crypto_ablkcipher {int dummy; } ;
struct chcr_context {int dummy; } ;

/* Variables and functions */
 struct chcr_context* crypto_ablkcipher_ctx (struct crypto_ablkcipher*) ; 

__attribute__((used)) static inline struct chcr_context *c_ctx(struct crypto_ablkcipher *tfm)
{
	return crypto_ablkcipher_ctx(tfm);
}