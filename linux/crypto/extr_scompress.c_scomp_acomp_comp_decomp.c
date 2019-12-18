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
struct scomp_scratch {int /*<<< orphan*/  lock; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct crypto_scomp {int dummy; } ;
struct crypto_acomp {int dummy; } ;
struct acomp_req {int /*<<< orphan*/  dlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  slen; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCOMP_SCRATCH_SIZE ; 
 void** acomp_request_ctx (struct acomp_req*) ; 
 void** acomp_tfm_ctx (struct crypto_acomp*) ; 
 struct crypto_acomp* crypto_acomp_reqtfm (struct acomp_req*) ; 
 int crypto_scomp_compress (struct crypto_scomp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int crypto_scomp_decompress (struct crypto_scomp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 struct scomp_scratch* raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scomp_scratch ; 
 int /*<<< orphan*/  sgl_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scomp_acomp_comp_decomp(struct acomp_req *req, int dir)
{
	struct crypto_acomp *tfm = crypto_acomp_reqtfm(req);
	void **tfm_ctx = acomp_tfm_ctx(tfm);
	struct crypto_scomp *scomp = *tfm_ctx;
	void **ctx = acomp_request_ctx(req);
	struct scomp_scratch *scratch;
	int ret;

	if (!req->src || !req->slen || req->slen > SCOMP_SCRATCH_SIZE)
		return -EINVAL;

	if (req->dst && !req->dlen)
		return -EINVAL;

	if (!req->dlen || req->dlen > SCOMP_SCRATCH_SIZE)
		req->dlen = SCOMP_SCRATCH_SIZE;

	scratch = raw_cpu_ptr(&scomp_scratch);
	spin_lock(&scratch->lock);

	scatterwalk_map_and_copy(scratch->src, req->src, 0, req->slen, 0);
	if (dir)
		ret = crypto_scomp_compress(scomp, scratch->src, req->slen,
					    scratch->dst, &req->dlen, *ctx);
	else
		ret = crypto_scomp_decompress(scomp, scratch->src, req->slen,
					      scratch->dst, &req->dlen, *ctx);
	if (!ret) {
		if (!req->dst) {
			req->dst = sgl_alloc(req->dlen, GFP_ATOMIC, NULL);
			if (!req->dst) {
				ret = -ENOMEM;
				goto out;
			}
		}
		scatterwalk_map_and_copy(scratch->dst, req->dst, 0, req->dlen,
					 1);
	}
out:
	spin_unlock(&scratch->lock);
	return ret;
}