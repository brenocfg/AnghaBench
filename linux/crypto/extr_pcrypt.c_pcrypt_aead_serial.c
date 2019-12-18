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
struct padata_priv {int /*<<< orphan*/  info; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct aead_request {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  aead_request_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcrypt_request* pcrypt_padata_request (struct padata_priv*) ; 
 struct aead_request* pcrypt_request_ctx (struct pcrypt_request*) ; 

__attribute__((used)) static void pcrypt_aead_serial(struct padata_priv *padata)
{
	struct pcrypt_request *preq = pcrypt_padata_request(padata);
	struct aead_request *req = pcrypt_request_ctx(preq);

	aead_request_complete(req->base.data, padata->info);
}