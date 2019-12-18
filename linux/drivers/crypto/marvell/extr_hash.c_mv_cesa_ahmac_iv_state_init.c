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
struct mv_cesa_ahash_result {int error; int /*<<< orphan*/  completion; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mv_cesa_ahash_result*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int crypto_ahash_export (struct ahash_request*,void*) ; 
 int crypto_ahash_init (struct ahash_request*) ; 
 int crypto_ahash_update (struct ahash_request*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_cesa_hmac_ahash_complete ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv_cesa_ahmac_iv_state_init(struct ahash_request *req, u8 *pad,
				       void *state, unsigned int blocksize)
{
	struct mv_cesa_ahash_result result;
	struct scatterlist sg;
	int ret;

	ahash_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   mv_cesa_hmac_ahash_complete, &result);
	sg_init_one(&sg, pad, blocksize);
	ahash_request_set_crypt(req, &sg, pad, blocksize);
	init_completion(&result.completion);

	ret = crypto_ahash_init(req);
	if (ret)
		return ret;

	ret = crypto_ahash_update(req);
	if (ret && ret != -EINPROGRESS)
		return ret;

	wait_for_completion_interruptible(&result.completion);
	if (result.error)
		return result.error;

	ret = crypto_ahash_export(req, state);
	if (ret)
		return ret;

	return 0;
}