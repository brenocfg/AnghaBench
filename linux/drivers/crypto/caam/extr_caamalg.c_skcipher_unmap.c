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
struct skcipher_request {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct skcipher_edesc {int /*<<< orphan*/  sec4_sg_bytes; int /*<<< orphan*/  sec4_sg_dma; int /*<<< orphan*/  iv_dma; int /*<<< orphan*/  dst_nents; int /*<<< orphan*/  src_nents; } ;
struct device {int dummy; } ;
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  caam_unmap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_skcipher_ivsize (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 

__attribute__((used)) static void skcipher_unmap(struct device *dev, struct skcipher_edesc *edesc,
			   struct skcipher_request *req)
{
	struct crypto_skcipher *skcipher = crypto_skcipher_reqtfm(req);
	int ivsize = crypto_skcipher_ivsize(skcipher);

	caam_unmap(dev, req->src, req->dst,
		   edesc->src_nents, edesc->dst_nents,
		   edesc->iv_dma, ivsize,
		   edesc->sec4_sg_dma, edesc->sec4_sg_bytes);
}