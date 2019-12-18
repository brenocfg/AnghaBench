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
typedef  size_t u32 ;
struct skd_fitmsg_context {scalar_t__ mb_dma_address; int /*<<< orphan*/ * msg_buf; } ;
struct skd_device {size_t num_fitmsg_context; struct skd_fitmsg_context* skmsg_table; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKD_N_FITMSG_BYTES ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct skd_fitmsg_context*) ; 

__attribute__((used)) static void skd_free_skmsg(struct skd_device *skdev)
{
	u32 i;

	if (skdev->skmsg_table == NULL)
		return;

	for (i = 0; i < skdev->num_fitmsg_context; i++) {
		struct skd_fitmsg_context *skmsg;

		skmsg = &skdev->skmsg_table[i];

		if (skmsg->msg_buf != NULL) {
			dma_free_coherent(&skdev->pdev->dev, SKD_N_FITMSG_BYTES,
					  skmsg->msg_buf,
					    skmsg->mb_dma_address);
		}
		skmsg->msg_buf = NULL;
		skmsg->mb_dma_address = 0;
	}

	kfree(skdev->skmsg_table);
	skdev->skmsg_table = NULL;
}