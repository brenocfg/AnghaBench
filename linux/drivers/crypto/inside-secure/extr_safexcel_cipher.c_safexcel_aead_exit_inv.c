#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct safexcel_inv_result {int dummy; } ;
struct safexcel_cipher_req {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct aead_request {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  EIP197_AEAD_REQ_SIZE ; 
 int /*<<< orphan*/  EIP197_REQUEST_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __crypto_aead_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  aead ; 
 struct safexcel_cipher_req* aead_request_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  aead_request_set_callback (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_inv_result*) ; 
 int /*<<< orphan*/  aead_request_set_tfm (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* req ; 
 int safexcel_cipher_exit_inv (struct crypto_tfm*,int /*<<< orphan*/ *,struct safexcel_cipher_req*,struct safexcel_inv_result*) ; 
 int /*<<< orphan*/  safexcel_inv_complete ; 

__attribute__((used)) static int safexcel_aead_exit_inv(struct crypto_tfm *tfm)
{
	EIP197_REQUEST_ON_STACK(req, aead, EIP197_AEAD_REQ_SIZE);
	struct safexcel_cipher_req *sreq = aead_request_ctx(req);
	struct safexcel_inv_result result = {};

	memset(req, 0, sizeof(struct aead_request));

	aead_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				  safexcel_inv_complete, &result);
	aead_request_set_tfm(req, __crypto_aead_cast(tfm));

	return safexcel_cipher_exit_inv(tfm, &req->base, sreq, &result);
}