#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pd_uinfo {int state; int /*<<< orphan*/  async_req; } ;
struct crypto4xx_device {int dummy; } ;
struct crypto4xx_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {TYPE_1__ base; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int PD_ENTRY_BUSY ; 
 struct ahash_request* ahash_request_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_complete (struct ahash_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto4xx_copy_digest_to_dst (int /*<<< orphan*/ ,struct pd_uinfo*,struct crypto4xx_ctx*) ; 
 int /*<<< orphan*/  crypto4xx_ret_sg_desc (struct crypto4xx_device*,struct pd_uinfo*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto4xx_ahash_done(struct crypto4xx_device *dev,
				struct pd_uinfo *pd_uinfo)
{
	struct crypto4xx_ctx *ctx;
	struct ahash_request *ahash_req;

	ahash_req = ahash_request_cast(pd_uinfo->async_req);
	ctx  = crypto_tfm_ctx(ahash_req->base.tfm);

	crypto4xx_copy_digest_to_dst(ahash_req->result, pd_uinfo,
				     crypto_tfm_ctx(ahash_req->base.tfm));
	crypto4xx_ret_sg_desc(dev, pd_uinfo);

	if (pd_uinfo->state & PD_ENTRY_BUSY)
		ahash_request_complete(ahash_req, -EINPROGRESS);
	ahash_request_complete(ahash_req, 0);
}