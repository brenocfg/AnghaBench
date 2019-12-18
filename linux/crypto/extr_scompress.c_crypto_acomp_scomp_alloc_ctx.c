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
struct crypto_tfm {int dummy; } ;
struct crypto_scomp {int dummy; } ;
struct crypto_acomp {int dummy; } ;
struct acomp_req {void** __ctx; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 struct crypto_acomp* crypto_acomp_reqtfm (struct acomp_req*) ; 
 struct crypto_tfm* crypto_acomp_tfm (struct crypto_acomp*) ; 
 void* crypto_scomp_alloc_ctx (struct crypto_scomp*) ; 
 struct crypto_scomp** crypto_tfm_ctx (struct crypto_tfm*) ; 
 int /*<<< orphan*/  kfree (struct acomp_req*) ; 

struct acomp_req *crypto_acomp_scomp_alloc_ctx(struct acomp_req *req)
{
	struct crypto_acomp *acomp = crypto_acomp_reqtfm(req);
	struct crypto_tfm *tfm = crypto_acomp_tfm(acomp);
	struct crypto_scomp **tfm_ctx = crypto_tfm_ctx(tfm);
	struct crypto_scomp *scomp = *tfm_ctx;
	void *ctx;

	ctx = crypto_scomp_alloc_ctx(scomp);
	if (IS_ERR(ctx)) {
		kfree(req);
		return NULL;
	}

	*req->__ctx = ctx;

	return req;
}