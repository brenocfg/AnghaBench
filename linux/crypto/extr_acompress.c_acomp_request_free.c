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
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct crypto_acomp {int /*<<< orphan*/  (* dst_free ) (int /*<<< orphan*/ *) ;} ;
struct acomp_req {int flags; int /*<<< orphan*/ * dst; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cra_type; } ;

/* Variables and functions */
 int CRYPTO_ACOMP_ALLOC_OUTPUT ; 
 int /*<<< orphan*/  __acomp_request_free (struct acomp_req*) ; 
 struct crypto_acomp* crypto_acomp_reqtfm (struct acomp_req*) ; 
 int /*<<< orphan*/  crypto_acomp_scomp_free_ctx (struct acomp_req*) ; 
 struct crypto_tfm* crypto_acomp_tfm (struct crypto_acomp*) ; 
 int /*<<< orphan*/  crypto_acomp_type ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void acomp_request_free(struct acomp_req *req)
{
	struct crypto_acomp *acomp = crypto_acomp_reqtfm(req);
	struct crypto_tfm *tfm = crypto_acomp_tfm(acomp);

	if (tfm->__crt_alg->cra_type != &crypto_acomp_type)
		crypto_acomp_scomp_free_ctx(req);

	if (req->flags & CRYPTO_ACOMP_ALLOC_OUTPUT) {
		acomp->dst_free(req->dst);
		req->dst = NULL;
	}

	__acomp_request_free(req);
}