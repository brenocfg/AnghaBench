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
struct zip_kernel_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 struct zip_kernel_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int zip_compress (int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,unsigned int*,struct zip_kernel_ctx*) ; 

int  zip_comp_compress(struct crypto_tfm *tfm,
		       const u8 *src, unsigned int slen,
		       u8 *dst, unsigned int *dlen)
{
	int ret;
	struct zip_kernel_ctx *zip_ctx = crypto_tfm_ctx(tfm);

	ret = zip_compress(src, slen, dst, dlen, zip_ctx);

	return ret;
}