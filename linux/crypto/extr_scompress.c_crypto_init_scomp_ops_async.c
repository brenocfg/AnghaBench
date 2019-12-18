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
struct crypto_tfm {int /*<<< orphan*/  exit; struct crypto_alg* __crt_alg; } ;
struct crypto_scomp {int dummy; } ;
struct crypto_alg {int dummy; } ;
struct crypto_acomp {int reqsize; int /*<<< orphan*/  dst_free; int /*<<< orphan*/  decompress; int /*<<< orphan*/  compress; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct crypto_scomp*) ; 
 int PTR_ERR (struct crypto_scomp*) ; 
 struct crypto_acomp* __crypto_acomp_tfm (struct crypto_tfm*) ; 
 struct crypto_scomp* crypto_create_tfm (struct crypto_alg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_exit_scomp_ops_async ; 
 int /*<<< orphan*/  crypto_mod_get (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_mod_put (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_scomp_type ; 
 struct crypto_scomp** crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  scomp_acomp_compress ; 
 int /*<<< orphan*/  scomp_acomp_decompress ; 
 int /*<<< orphan*/  sgl_free ; 

int crypto_init_scomp_ops_async(struct crypto_tfm *tfm)
{
	struct crypto_alg *calg = tfm->__crt_alg;
	struct crypto_acomp *crt = __crypto_acomp_tfm(tfm);
	struct crypto_scomp **ctx = crypto_tfm_ctx(tfm);
	struct crypto_scomp *scomp;

	if (!crypto_mod_get(calg))
		return -EAGAIN;

	scomp = crypto_create_tfm(calg, &crypto_scomp_type);
	if (IS_ERR(scomp)) {
		crypto_mod_put(calg);
		return PTR_ERR(scomp);
	}

	*ctx = scomp;
	tfm->exit = crypto_exit_scomp_ops_async;

	crt->compress = scomp_acomp_compress;
	crt->decompress = scomp_acomp_decompress;
	crt->dst_free = sgl_free;
	crt->reqsize = sizeof(void *);

	return 0;
}