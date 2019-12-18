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
struct skcipher_request {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFEXCEL_DECRYPT ; 
 int safexcel_queue_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int safexcel_decrypt(struct skcipher_request *req)
{
	return safexcel_queue_req(&req->base, skcipher_request_ctx(req),
			SAFEXCEL_DECRYPT);
}