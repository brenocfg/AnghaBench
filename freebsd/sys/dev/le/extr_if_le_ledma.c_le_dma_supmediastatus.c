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
struct lsi64854_softc {int dummy; } ;
struct le_dma_softc {struct lsi64854_softc* sc_dma; } ;
struct lance_softc {int dummy; } ;
struct ifmediareq {void* ifm_active; } ;

/* Variables and functions */
 int E_TP_AUI ; 
 int /*<<< orphan*/  IFM_10_5 ; 
 int /*<<< orphan*/  IFM_10_T ; 
 int /*<<< orphan*/  IFM_ETHER ; 
 void* IFM_MAKEWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int L64854_GCSR (struct lsi64854_softc*) ; 

__attribute__((used)) static void
le_dma_supmediastatus(struct lance_softc *sc, struct ifmediareq *ifmr)
{
	struct lsi64854_softc *dma = ((struct le_dma_softc *)sc)->sc_dma;

	/*
	 * Notify the world which media we're currently using.
	 */
	if (L64854_GCSR(dma) & E_TP_AUI)
		ifmr->ifm_active = IFM_MAKEWORD(IFM_ETHER, IFM_10_T, 0, 0);
	else
		ifmr->ifm_active = IFM_MAKEWORD(IFM_ETHER, IFM_10_5, 0, 0);
}