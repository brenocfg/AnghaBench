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
struct linux_dma_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  ptree; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct linux_dma_priv*,int /*<<< orphan*/ ) ; 
 int linux_dma_tag_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct linux_dma_priv* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pctrie_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_pdev_dma_init(struct pci_dev *pdev)
{
	struct linux_dma_priv *priv;
	int error;

	priv = malloc(sizeof(*priv), M_DEVBUF, M_WAITOK | M_ZERO);
	pdev->dev.dma_priv = priv;

	mtx_init(&priv->lock, "lkpi-priv-dma", NULL, MTX_DEF);

	pctrie_init(&priv->ptree);

	/* create a default DMA tag */
	error = linux_dma_tag_init(&pdev->dev, DMA_BIT_MASK(64));
	if (error) {
		mtx_destroy(&priv->lock);
		free(priv, M_DEVBUF);
		pdev->dev.dma_priv = NULL;
	}
	return (error);
}