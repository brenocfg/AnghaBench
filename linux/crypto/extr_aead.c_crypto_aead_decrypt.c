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
struct crypto_alg {int dummy; } ;
struct TYPE_3__ {struct crypto_alg* __crt_alg; } ;
struct crypto_aead {TYPE_1__ base; } ;
struct aead_request {unsigned int cryptlen; } ;
struct TYPE_4__ {int (* decrypt ) (struct aead_request*) ;} ;

/* Variables and functions */
 int CRYPTO_TFM_NEED_KEY ; 
 int EINVAL ; 
 int ENOKEY ; 
 TYPE_2__* crypto_aead_alg (struct crypto_aead*) ; 
 scalar_t__ crypto_aead_authsize (struct crypto_aead*) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_stats_aead_decrypt (unsigned int,struct crypto_alg*,int) ; 
 int /*<<< orphan*/  crypto_stats_get (struct crypto_alg*) ; 
 int stub1 (struct aead_request*) ; 

int crypto_aead_decrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_alg *alg = aead->base.__crt_alg;
	unsigned int cryptlen = req->cryptlen;
	int ret;

	crypto_stats_get(alg);
	if (crypto_aead_get_flags(aead) & CRYPTO_TFM_NEED_KEY)
		ret = -ENOKEY;
	else if (req->cryptlen < crypto_aead_authsize(aead))
		ret = -EINVAL;
	else
		ret = crypto_aead_alg(aead)->decrypt(req);
	crypto_stats_aead_decrypt(cryptlen, alg, ret);
	return ret;
}