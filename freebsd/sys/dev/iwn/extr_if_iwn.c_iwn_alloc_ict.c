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
struct iwn_softc {int /*<<< orphan*/  ict; int /*<<< orphan*/  ict_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_ICT_SIZE ; 
 int iwn_dma_contig_alloc (struct iwn_softc*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwn_alloc_ict(struct iwn_softc *sc)
{
	/* ICT table must be aligned on a 4KB boundary. */
	return iwn_dma_contig_alloc(sc, &sc->ict_dma, (void **)&sc->ict,
	    IWN_ICT_SIZE, 4096);
}