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
typedef  scalar_t__ u32 ;
struct qce_algo_ops {scalar_t__ type; int (* async_req_handle ) (struct crypto_async_request*) ;} ;
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct qce_algo_ops**) ; 
 int EINVAL ; 
 scalar_t__ crypto_tfm_alg_type (int /*<<< orphan*/ ) ; 
 struct qce_algo_ops** qce_ops ; 
 int stub1 (struct crypto_async_request*) ; 

__attribute__((used)) static int qce_handle_request(struct crypto_async_request *async_req)
{
	int ret = -EINVAL, i;
	const struct qce_algo_ops *ops;
	u32 type = crypto_tfm_alg_type(async_req->tfm);

	for (i = 0; i < ARRAY_SIZE(qce_ops); i++) {
		ops = qce_ops[i];
		if (type != ops->type)
			continue;
		ret = ops->async_req_handle(async_req);
		break;
	}

	return ret;
}