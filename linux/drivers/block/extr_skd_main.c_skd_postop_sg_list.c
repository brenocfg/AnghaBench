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
struct skd_request_context {int n_sg; int /*<<< orphan*/  data_dir; int /*<<< orphan*/ * sg; scalar_t__ sksg_dma_address; TYPE_1__* sksg_list; } ;
struct skd_device {TYPE_2__* pdev; } ;
struct fit_sg_descriptor {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ next_desc_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skd_postop_sg_list(struct skd_device *skdev,
			       struct skd_request_context *skreq)
{
	/*
	 * restore the next ptr for next IO request so we
	 * don't have to set it every time.
	 */
	skreq->sksg_list[skreq->n_sg - 1].next_desc_ptr =
		skreq->sksg_dma_address +
		((skreq->n_sg) * sizeof(struct fit_sg_descriptor));
	dma_unmap_sg(&skdev->pdev->dev, &skreq->sg[0], skreq->n_sg,
		     skreq->data_dir);
}