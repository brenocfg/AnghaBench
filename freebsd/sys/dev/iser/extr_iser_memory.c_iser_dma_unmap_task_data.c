#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iser_data_buf {int /*<<< orphan*/  size; int /*<<< orphan*/  sgl; } ;
struct icl_iser_pdu {TYPE_3__* iser_conn; } ;
struct ib_device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ ib_conn; } ;
struct TYPE_4__ {struct ib_device* ib_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dma_unmap_sg (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
iser_dma_unmap_task_data(struct icl_iser_pdu *iser_pdu,
			 struct iser_data_buf *data,
			 enum dma_data_direction dir)
{
	struct ib_device *dev;

	dev = iser_pdu->iser_conn->ib_conn.device->ib_device;
	ib_dma_unmap_sg(dev, data->sgl, data->size, dir);
}