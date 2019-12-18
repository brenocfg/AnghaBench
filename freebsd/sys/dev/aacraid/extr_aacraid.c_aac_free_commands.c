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
struct aac_softc {int aac_max_fibs_alloc; int /*<<< orphan*/  aac_fib_dmat; int /*<<< orphan*/  aac_buffer_dmat; int /*<<< orphan*/  total_fibs; int /*<<< orphan*/  aac_fibmap_tqh; } ;
struct aac_fibmap {int /*<<< orphan*/  aac_fibmap; int /*<<< orphan*/  aac_fibs; struct aac_command* aac_commands; } ;
struct aac_command {int /*<<< orphan*/  cm_datamap; } ;

/* Variables and functions */
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACRAIDBUF ; 
 struct aac_fibmap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct aac_fibmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_link ; 
 int /*<<< orphan*/  free (struct aac_fibmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static void
aac_free_commands(struct aac_softc *sc)
{
	struct aac_fibmap *fm;
	struct aac_command *cm;
	int i;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	while ((fm = TAILQ_FIRST(&sc->aac_fibmap_tqh)) != NULL) {

		TAILQ_REMOVE(&sc->aac_fibmap_tqh, fm, fm_link);
		/*
		 * We check against total_fibs to handle partially
		 * allocated blocks.
		 */
		for (i = 0; i < sc->aac_max_fibs_alloc && sc->total_fibs--; i++) {
			cm = fm->aac_commands + i;
			bus_dmamap_destroy(sc->aac_buffer_dmat, cm->cm_datamap);
		}
		bus_dmamap_unload(sc->aac_fib_dmat, fm->aac_fibmap);
		bus_dmamem_free(sc->aac_fib_dmat, fm->aac_fibs, fm->aac_fibmap);
		free(fm, M_AACRAIDBUF);
	}
}