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
struct skcipher_request {int dummy; } ;
struct safexcel_inv_result {int dummy; } ;
struct safexcel_cipher_req {int dummy; } ;
struct crypto_tfm {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int /*<<< orphan*/  EIP197_REQUEST_ON_STACK (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIP197_SKCIPHER_REQ_SIZE ; 
 int /*<<< orphan*/  __crypto_skcipher_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* req ; 
 int safexcel_cipher_exit_inv (struct crypto_tfm*,int /*<<< orphan*/ *,struct safexcel_cipher_req*,struct safexcel_inv_result*) ; 
 int /*<<< orphan*/  safexcel_inv_complete ; 
 int /*<<< orphan*/  skcipher ; 
 struct safexcel_cipher_req* skcipher_request_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_inv_result*) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int safexcel_skcipher_exit_inv(struct crypto_tfm *tfm)
{
	EIP197_REQUEST_ON_STACK(req, skcipher, EIP197_SKCIPHER_REQ_SIZE);
	struct safexcel_cipher_req *sreq = skcipher_request_ctx(req);
	struct safexcel_inv_result result = {};

	memset(req, 0, sizeof(struct skcipher_request));

	skcipher_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				      safexcel_inv_complete, &result);
	skcipher_request_set_tfm(req, __crypto_skcipher_cast(tfm));

	return safexcel_cipher_exit_inv(tfm, &req->base, sreq, &result);
}