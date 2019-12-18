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
struct adapter {scalar_t__ dmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 

int
t4_destroy_dma_tag(struct adapter *sc)
{
	if (sc->dmat)
		bus_dma_tag_destroy(sc->dmat);

	return (0);
}