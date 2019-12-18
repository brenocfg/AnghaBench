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
struct skcipher_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  src; int /*<<< orphan*/  iv; } ;
struct nitrox_kcrypt_request {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int alloc_src_req_buf (struct nitrox_kcrypt_request*,int,int) ; 
 int /*<<< orphan*/  nitrox_creq_copy_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nitrox_creq_set_src_sg (struct nitrox_kcrypt_request*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sg_nents (int /*<<< orphan*/ ) ; 
 struct nitrox_kcrypt_request* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int alloc_src_sglist(struct skcipher_request *skreq, int ivsize)
{
	struct nitrox_kcrypt_request *nkreq = skcipher_request_ctx(skreq);
	int nents = sg_nents(skreq->src) + 1;
	int ret;

	/* Allocate buffer to hold IV and input scatterlist array */
	ret = alloc_src_req_buf(nkreq, nents, ivsize);
	if (ret)
		return ret;

	nitrox_creq_copy_iv(nkreq->src, skreq->iv, ivsize);
	nitrox_creq_set_src_sg(nkreq, nents, ivsize, skreq->src,
			       skreq->cryptlen);

	return 0;
}