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
struct mwl_softc {int dummy; } ;
struct mwl_descdma {int /*<<< orphan*/  dd_dmat; int /*<<< orphan*/  dd_dmamap; int /*<<< orphan*/  dd_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mwl_descdma*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mwl_desc_cleanup(struct mwl_softc *sc, struct mwl_descdma *dd)
{
	bus_dmamap_unload(dd->dd_dmat, dd->dd_dmamap);
	bus_dmamem_free(dd->dd_dmat, dd->dd_desc, dd->dd_dmamap);
	bus_dma_tag_destroy(dd->dd_dmat);

	memset(dd, 0, sizeof(*dd));
}