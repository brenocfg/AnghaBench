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
struct ssh_hmac_ctx {int alg; int buf_len; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * ictx; int /*<<< orphan*/ * digest; int /*<<< orphan*/ * octx; } ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int ssh_digest_blocksize (int /*<<< orphan*/ *) ; 
 void* ssh_digest_start (int) ; 
 int /*<<< orphan*/  ssh_hmac_free (struct ssh_hmac_ctx*) ; 

struct ssh_hmac_ctx *
ssh_hmac_start(int alg)
{
	struct ssh_hmac_ctx	*ret;

	if ((ret = calloc(1, sizeof(*ret))) == NULL)
		return NULL;
	ret->alg = alg;
	if ((ret->ictx = ssh_digest_start(alg)) == NULL ||
	    (ret->octx = ssh_digest_start(alg)) == NULL ||
	    (ret->digest = ssh_digest_start(alg)) == NULL)
		goto fail;
	ret->buf_len = ssh_digest_blocksize(ret->ictx);
	if ((ret->buf = calloc(1, ret->buf_len)) == NULL)
		goto fail;
	return ret;
fail:
	ssh_hmac_free(ret);
	return NULL;
}