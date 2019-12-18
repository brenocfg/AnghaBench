#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct crypto_alg {int dummy; } ;
struct TYPE_2__ {struct crypto_alg* __crt_alg; } ;
struct crypto_ahash {int /*<<< orphan*/  final; TYPE_1__ base; } ;
struct ahash_request {unsigned int nbytes; } ;

/* Variables and functions */
 int crypto_ahash_op (struct ahash_request*,int /*<<< orphan*/ ) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  crypto_stats_ahash_final (unsigned int,int,struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_stats_get (struct crypto_alg*) ; 

int crypto_ahash_final(struct ahash_request *req)
{
	struct crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	struct crypto_alg *alg = tfm->base.__crt_alg;
	unsigned int nbytes = req->nbytes;
	int ret;

	crypto_stats_get(alg);
	ret = crypto_ahash_op(req, crypto_ahash_reqtfm(req)->final);
	crypto_stats_ahash_final(nbytes, ret, alg);
	return ret;
}