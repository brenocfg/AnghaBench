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
struct iwn_softc {int /*<<< orphan*/  schedsz; int /*<<< orphan*/  sched; int /*<<< orphan*/  sched_dma; } ;

/* Variables and functions */
 int iwn_dma_contig_alloc (struct iwn_softc*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwn_alloc_sched(struct iwn_softc *sc)
{
	/* TX scheduler rings must be aligned on a 1KB boundary. */
	return iwn_dma_contig_alloc(sc, &sc->sched_dma, (void **)&sc->sched,
	    sc->schedsz, 1024);
}