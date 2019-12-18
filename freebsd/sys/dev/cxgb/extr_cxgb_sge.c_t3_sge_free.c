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
struct adapter {int /*<<< orphan*/ * parent_dmat; int /*<<< orphan*/ * rx_dmat; int /*<<< orphan*/ * rx_jumbo_dmat; int /*<<< orphan*/ * tx_dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 

int
t3_sge_free(struct adapter * sc)
{

	if (sc->tx_dmat != NULL)
		bus_dma_tag_destroy(sc->tx_dmat);

	if (sc->rx_jumbo_dmat != NULL)
		bus_dma_tag_destroy(sc->rx_jumbo_dmat);

	if (sc->rx_dmat != NULL)
		bus_dma_tag_destroy(sc->rx_dmat);

	if (sc->parent_dmat != NULL)
		bus_dma_tag_destroy(sc->parent_dmat);

	return (0);
}