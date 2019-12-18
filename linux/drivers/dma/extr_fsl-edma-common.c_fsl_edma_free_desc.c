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
struct virt_dma_desc {int dummy; } ;
struct fsl_edma_desc {int n_tcds; TYPE_2__* tcd; TYPE_1__* echan; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptcd; int /*<<< orphan*/  vtcd; } ;
struct TYPE_3__ {int /*<<< orphan*/  tcd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fsl_edma_desc*) ; 
 struct fsl_edma_desc* to_fsl_edma_desc (struct virt_dma_desc*) ; 

void fsl_edma_free_desc(struct virt_dma_desc *vdesc)
{
	struct fsl_edma_desc *fsl_desc;
	int i;

	fsl_desc = to_fsl_edma_desc(vdesc);
	for (i = 0; i < fsl_desc->n_tcds; i++)
		dma_pool_free(fsl_desc->echan->tcd_pool, fsl_desc->tcd[i].vtcd,
			      fsl_desc->tcd[i].ptcd);
	kfree(fsl_desc);
}