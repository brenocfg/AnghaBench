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
struct iwn_softc {int /*<<< orphan*/  ict_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwn_dma_contig_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iwn_free_ict(struct iwn_softc *sc)
{
	iwn_dma_contig_free(&sc->ict_dma);
}