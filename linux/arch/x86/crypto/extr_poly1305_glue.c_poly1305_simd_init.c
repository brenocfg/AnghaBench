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
struct shash_desc {int dummy; } ;
struct poly1305_simd_desc_ctx {int uset; int wset; } ;

/* Variables and functions */
 int crypto_poly1305_init (struct shash_desc*) ; 
 struct poly1305_simd_desc_ctx* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int poly1305_simd_init(struct shash_desc *desc)
{
	struct poly1305_simd_desc_ctx *sctx = shash_desc_ctx(desc);

	sctx->uset = false;
#ifdef CONFIG_AS_AVX2
	sctx->wset = false;
#endif

	return crypto_poly1305_init(desc);
}