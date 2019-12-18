#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  length; int /*<<< orphan*/  lkey; } ;
struct iser_mem_reg {TYPE_1__ sge; int /*<<< orphan*/  rkey; } ;
struct iser_device {int /*<<< orphan*/  ib_device; TYPE_2__* mr; } ;
struct iser_data_buf {struct scatterlist* sgl; } ;
struct TYPE_4__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_sg_dma_address (int /*<<< orphan*/ ,struct scatterlist*) ; 
 int /*<<< orphan*/  ib_sg_dma_len (int /*<<< orphan*/ ,struct scatterlist*) ; 

__attribute__((used)) static int
iser_reg_dma(struct iser_device *device, struct iser_data_buf *mem,
	     struct iser_mem_reg *reg)
{
	struct scatterlist *sg = mem->sgl;

	reg->sge.lkey = device->mr->lkey;
	reg->rkey = device->mr->rkey;
	reg->sge.length = ib_sg_dma_len(device->ib_device, &sg[0]);
	reg->sge.addr = ib_sg_dma_address(device->ib_device, &sg[0]);

	return (0);
}