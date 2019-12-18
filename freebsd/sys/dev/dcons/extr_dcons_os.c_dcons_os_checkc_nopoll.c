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
struct dcons_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * dma_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dcons_check_break (struct dcons_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcons_checkc (struct dcons_softc*) ; 
 TYPE_1__ dg ; 

__attribute__((used)) static int
dcons_os_checkc_nopoll(struct dcons_softc *dc)
{
	int c;

	if (dg.dma_tag != NULL)
		bus_dmamap_sync(dg.dma_tag, dg.dma_map, BUS_DMASYNC_POSTREAD);

	c = dcons_check_break(dc, dcons_checkc(dc));

	if (dg.dma_tag != NULL)
		bus_dmamap_sync(dg.dma_tag, dg.dma_map, BUS_DMASYNC_PREREAD);

	return (c);
}