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
struct skcipher_request {int dummy; } ;
struct crypto_async_request {struct skcipher_request* data; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int cts_cbc_decrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_complete (struct skcipher_request*,int) ; 

__attribute__((used)) static void crypto_cts_decrypt_done(struct crypto_async_request *areq, int err)
{
	struct skcipher_request *req = areq->data;

	if (err)
		goto out;

	err = cts_cbc_decrypt(req);
	if (err == -EINPROGRESS || err == -EBUSY)
		return;

out:
	skcipher_request_complete(req, err);
}