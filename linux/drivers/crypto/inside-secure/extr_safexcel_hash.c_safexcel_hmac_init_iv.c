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
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct safexcel_ahash_result {int error; int /*<<< orphan*/  completion; } ;
struct safexcel_ahash_req {int hmac; int last_req; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_ahash_result*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_ahash_export (struct ahash_request*,void*) ; 
 int crypto_ahash_init (struct ahash_request*) ; 
 int crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safexcel_ahash_complete ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int safexcel_hmac_init_iv(struct ahash_request *areq,
				 unsigned int blocksize, u8 *pad, void *state)
{
	struct safexcel_ahash_result result;
	struct safexcel_ahash_req *req;
	struct scatterlist sg;
	int ret;

	ahash_request_set_callback(areq, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   safexcel_ahash_complete, &result);
	sg_init_one(&sg, pad, blocksize);
	ahash_request_set_crypt(areq, &sg, pad, blocksize);
	init_completion(&result.completion);

	ret = crypto_ahash_init(areq);
	if (ret)
		return ret;

	req = ahash_request_ctx(areq);
	req->hmac = true;
	req->last_req = true;

	ret = crypto_ahash_update(areq);
	if (ret && ret != -EINPROGRESS && ret != -EBUSY)
		return ret;

	wait_for_completion_interruptible(&result.completion);
	if (result.error)
		return result.error;

	return crypto_ahash_export(areq, state);
}