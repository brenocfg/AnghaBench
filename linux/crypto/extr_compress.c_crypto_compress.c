#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_tfm {TYPE_2__* __crt_alg; } ;
struct TYPE_3__ {int (* coa_compress ) (struct crypto_tfm*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,unsigned int*) ;} ;
struct TYPE_4__ {TYPE_1__ cra_compress; } ;

/* Variables and functions */
 int stub1 (struct crypto_tfm*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int crypto_compress(struct crypto_tfm *tfm,
                            const u8 *src, unsigned int slen,
                            u8 *dst, unsigned int *dlen)
{
	return tfm->__crt_alg->cra_compress.coa_compress(tfm, src, slen, dst,
	                                                 dlen);
}