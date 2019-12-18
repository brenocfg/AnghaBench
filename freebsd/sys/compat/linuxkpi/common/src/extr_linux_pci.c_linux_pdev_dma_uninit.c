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
struct TYPE_2__ {struct linux_dma_priv* dma_priv; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct linux_dma_priv {int /*<<< orphan*/  lock; scalar_t__ dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  free (struct linux_dma_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_pdev_dma_uninit(struct pci_dev *pdev)
{
	struct linux_dma_priv *priv;

	priv = pdev->dev.dma_priv;
	if (priv->dmat)
		bus_dma_tag_destroy(priv->dmat);
	mtx_destroy(&priv->lock);
	free(priv, M_DEVBUF);
	pdev->dev.dma_priv = NULL;
	return (0);
}