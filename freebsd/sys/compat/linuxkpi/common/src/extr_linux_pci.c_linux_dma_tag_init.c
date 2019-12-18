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
typedef  scalar_t__ u64 ;
struct linux_dma_priv {scalar_t__ dma_mask; scalar_t__ dmat; } ;
struct device {int /*<<< orphan*/  bsddev; struct linux_dma_priv* dma_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 

int
linux_dma_tag_init(struct device *dev, u64 dma_mask)
{
	struct linux_dma_priv *priv;
	int error;

	priv = dev->dma_priv;

	if (priv->dmat) {
		if (priv->dma_mask == dma_mask)
			return (0);

		bus_dma_tag_destroy(priv->dmat);
	}

	priv->dma_mask = dma_mask;

	error = bus_dma_tag_create(bus_get_dma_tag(dev->bsddev),
	    1, 0,			/* alignment, boundary */
	    dma_mask,			/* lowaddr */
	    BUS_SPACE_MAXADDR,		/* highaddr */
	    NULL, NULL,			/* filtfunc, filtfuncarg */
	    BUS_SPACE_MAXSIZE,		/* maxsize */
	    1,				/* nsegments */
	    BUS_SPACE_MAXSIZE,		/* maxsegsz */
	    0,				/* flags */
	    NULL, NULL,			/* lockfunc, lockfuncarg */
	    &priv->dmat);
	return (-error);
}