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
struct se_crypto_request {int /*<<< orphan*/ * dst; } ;
struct TYPE_2__ {int sgmap_cnt; int /*<<< orphan*/ * sg; } ;
struct nitrox_softreq {TYPE_1__ out; int /*<<< orphan*/  ndev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EINVAL ; 
 int create_sg_component (struct nitrox_softreq*,TYPE_1__*,int) ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dma_map_outbufs(struct nitrox_softreq *sr,
			   struct se_crypto_request *req)
{
	struct device *dev = DEV(sr->ndev);
	int nents, ret = 0;

	nents = dma_map_sg(dev, req->dst, sg_nents(req->dst),
			   DMA_BIDIRECTIONAL);
	if (!nents)
		return -EINVAL;

	sr->out.sg = req->dst;
	sr->out.sgmap_cnt = nents;
	ret = create_sg_component(sr, &sr->out, sr->out.sgmap_cnt);
	if (ret)
		goto outcomp_map_err;

	return 0;

outcomp_map_err:
	dma_unmap_sg(dev, req->dst, nents, DMA_BIDIRECTIONAL);
	sr->out.sgmap_cnt = 0;
	sr->out.sg = NULL;
	return ret;
}