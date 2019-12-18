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
struct crypto_async_request {struct aead_request* data; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 int gcm_hash_len_continue (struct aead_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gcm_hash_len_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;

	if (err)
		goto out;

	err = gcm_hash_len_continue(req, 0);
	if (err == -EINPROGRESS)
		return;

out:
	aead_request_complete(req, err);
}