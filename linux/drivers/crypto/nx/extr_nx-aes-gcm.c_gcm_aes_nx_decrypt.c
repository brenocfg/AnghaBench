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
struct nx_gcm_rctx {char* iv; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GCM_AES_IV_SIZE ; 
 struct nx_gcm_rctx* aead_request_ctx (struct aead_request*) ; 
 int gcm_aes_nx_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gcm_aes_nx_decrypt(struct aead_request *req)
{
	struct nx_gcm_rctx *rctx = aead_request_ctx(req);
	char *iv = rctx->iv;

	memcpy(iv, req->iv, GCM_AES_IV_SIZE);

	return gcm_aes_nx_crypt(req, 0, req->assoclen);
}