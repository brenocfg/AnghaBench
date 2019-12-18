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
struct wpi_softc {int /*<<< orphan*/  shared; int /*<<< orphan*/  shared_dma; } ;
struct wpi_shared {int dummy; } ;

/* Variables and functions */
 int wpi_dma_contig_alloc (struct wpi_softc*,int /*<<< orphan*/ *,void**,int,int) ; 

__attribute__((used)) static int
wpi_alloc_shared(struct wpi_softc *sc)
{
	/* Shared buffer must be aligned on a 4KB boundary. */
	return wpi_dma_contig_alloc(sc, &sc->shared_dma,
	    (void **)&sc->shared, sizeof (struct wpi_shared), 4096);
}