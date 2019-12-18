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
struct pcrypt_request {int dummy; } ;
struct padata_priv {int /*<<< orphan*/  info; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  crypto_aead_decrypt (struct aead_request*) ; 
 int /*<<< orphan*/  padata_do_serial (struct padata_priv*) ; 
 struct pcrypt_request* pcrypt_padata_request (struct padata_priv*) ; 
 struct aead_request* pcrypt_request_ctx (struct pcrypt_request*) ; 

__attribute__((used)) static void pcrypt_aead_dec(struct padata_priv *padata)
{
	struct pcrypt_request *preq = pcrypt_padata_request(padata);
	struct aead_request *req = pcrypt_request_ctx(preq);

	padata->info = crypto_aead_decrypt(req);

	if (padata->info == -EINPROGRESS)
		return;

	padata_do_serial(padata);
}