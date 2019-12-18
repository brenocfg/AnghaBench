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
struct ecdh_ctx {int ndigits; } ;
struct crypto_kpp {int dummy; } ;

/* Variables and functions */
 int ECC_DIGITS_TO_BYTES_SHIFT ; 
 struct ecdh_ctx* ecdh_get_ctx (struct crypto_kpp*) ; 

__attribute__((used)) static unsigned int ecdh_max_size(struct crypto_kpp *tfm)
{
	struct ecdh_ctx *ctx = ecdh_get_ctx(tfm);

	/* Public key is made of two coordinates, add one to the left shift */
	return ctx->ndigits << (ECC_DIGITS_TO_BYTES_SHIFT + 1);
}