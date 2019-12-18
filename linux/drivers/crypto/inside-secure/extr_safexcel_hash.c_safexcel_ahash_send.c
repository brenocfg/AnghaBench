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
struct safexcel_ahash_req {scalar_t__ needs_inv; } ;
struct crypto_async_request {int dummy; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct safexcel_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int safexcel_ahash_send_inv (struct crypto_async_request*,int,int*,int*) ; 
 int safexcel_ahash_send_req (struct crypto_async_request*,int,int*,int*) ; 

__attribute__((used)) static int safexcel_ahash_send(struct crypto_async_request *async,
			       int ring, int *commands, int *results)
{
	struct ahash_request *areq = ahash_request_cast(async);
	struct safexcel_ahash_req *req = ahash_request_ctx(areq);
	int ret;

	if (req->needs_inv)
		ret = safexcel_ahash_send_inv(async, ring, commands, results);
	else
		ret = safexcel_ahash_send_req(async, ring, commands, results);

	return ret;
}