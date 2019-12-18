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
struct virt_dma_desc {int /*<<< orphan*/  tx; } ;
struct mdc_tx_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mdc_tx_desc*) ; 
 int /*<<< orphan*/  mdc_list_desc_free (struct mdc_tx_desc*) ; 
 struct mdc_tx_desc* to_mdc_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mdc_desc_free(struct virt_dma_desc *vd)
{
	struct mdc_tx_desc *mdesc = to_mdc_desc(&vd->tx);

	mdc_list_desc_free(mdesc);
	kfree(mdesc);
}