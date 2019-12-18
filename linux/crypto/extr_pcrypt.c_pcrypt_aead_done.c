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
struct pcrypt_request {int dummy; } ;
struct padata_priv {int info; } ;
struct crypto_async_request {struct aead_request* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct aead_request {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 struct pcrypt_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  padata_do_serial (struct padata_priv*) ; 
 struct padata_priv* pcrypt_request_padata (struct pcrypt_request*) ; 

__attribute__((used)) static void pcrypt_aead_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;
	struct pcrypt_request *preq = aead_request_ctx(req);
	struct padata_priv *padata = pcrypt_request_padata(preq);

	padata->info = err;
	req->base.flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;

	padata_do_serial(padata);
}