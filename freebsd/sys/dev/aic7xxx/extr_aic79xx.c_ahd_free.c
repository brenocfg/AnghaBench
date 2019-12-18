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
struct TYPE_2__ {int /*<<< orphan*/  dmamap; } ;
struct ahd_tmode_tstate {int init_level; struct ahd_tmode_tstate* saved_stack; struct ahd_tmode_tstate* seep_config; struct ahd_tmode_tstate* name; struct ahd_tmode_tstate* black_hole; int /*<<< orphan*/  path; struct ahd_tmode_tstate** enabled_luns; struct ahd_tmode_tstate** enabled_targets; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/  shared_data_dmat; TYPE_1__ shared_data_map; int /*<<< orphan*/  qoutfifo; } ;
struct ahd_tmode_lstate {int init_level; struct ahd_tmode_lstate* saved_stack; struct ahd_tmode_lstate* seep_config; struct ahd_tmode_lstate* name; struct ahd_tmode_lstate* black_hole; int /*<<< orphan*/  path; struct ahd_tmode_lstate** enabled_luns; struct ahd_tmode_lstate** enabled_targets; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/  shared_data_dmat; TYPE_1__ shared_data_map; int /*<<< orphan*/  qoutfifo; } ;
struct ahd_softc {int init_level; struct ahd_softc* saved_stack; struct ahd_softc* seep_config; struct ahd_softc* name; struct ahd_softc* black_hole; int /*<<< orphan*/  path; struct ahd_softc** enabled_luns; struct ahd_softc** enabled_targets; int /*<<< orphan*/  parent_dmat; int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/  shared_data_dmat; TYPE_1__ shared_data_map; int /*<<< orphan*/  qoutfifo; } ;

/* Variables and functions */
 int AHD_NUM_LUNS ; 
 int AHD_NUM_TARGETS ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  ahd_fini_scbdata (struct ahd_tmode_tstate*) ; 
 int /*<<< orphan*/  ahd_platform_free (struct ahd_tmode_tstate*) ; 
 int /*<<< orphan*/  ahd_shutdown (struct ahd_tmode_tstate*) ; 
 int /*<<< orphan*/  ahd_terminate_recovery_thread (struct ahd_tmode_tstate*) ; 
 int /*<<< orphan*/  aic_dma_tag_destroy (struct ahd_tmode_tstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_dmamap_unload (struct ahd_tmode_tstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_dmamem_free (struct ahd_tmode_tstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ahd_tmode_tstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

void
ahd_free(struct ahd_softc *ahd)
{
	int i;

	ahd_terminate_recovery_thread(ahd);
	switch (ahd->init_level) {
	default:
	case 5:
		ahd_shutdown(ahd);
		/* FALLTHROUGH */
	case 4:
		aic_dmamap_unload(ahd, ahd->shared_data_dmat,
				  ahd->shared_data_map.dmamap);
		/* FALLTHROUGH */
	case 3:
		aic_dmamem_free(ahd, ahd->shared_data_dmat, ahd->qoutfifo,
				ahd->shared_data_map.dmamap);
		/* FALLTHROUGH */
	case 2:
		aic_dma_tag_destroy(ahd, ahd->shared_data_dmat);
	case 1:
#ifndef __linux__
		aic_dma_tag_destroy(ahd, ahd->buffer_dmat);
#endif
		break;
	case 0:
		break;
	}

#ifndef __linux__
	aic_dma_tag_destroy(ahd, ahd->parent_dmat);
#endif
	ahd_platform_free(ahd);
	ahd_fini_scbdata(ahd);
	for (i = 0; i < AHD_NUM_TARGETS; i++) {
		struct ahd_tmode_tstate *tstate;

		tstate = ahd->enabled_targets[i];
		if (tstate != NULL) {
#ifdef AHD_TARGET_MODE
			int j;

			for (j = 0; j < AHD_NUM_LUNS; j++) {
				struct ahd_tmode_lstate *lstate;

				lstate = tstate->enabled_luns[j];
				if (lstate != NULL) {
					xpt_free_path(lstate->path);
					free(lstate, M_DEVBUF);
				}
			}
#endif
			free(tstate, M_DEVBUF);
		}
	}
#ifdef AHD_TARGET_MODE
	if (ahd->black_hole != NULL) {
		xpt_free_path(ahd->black_hole->path);
		free(ahd->black_hole, M_DEVBUF);
	}
#endif
	if (ahd->name != NULL)
		free(ahd->name, M_DEVBUF);
	if (ahd->seep_config != NULL)
		free(ahd->seep_config, M_DEVBUF);
	if (ahd->saved_stack != NULL)
		free(ahd->saved_stack, M_DEVBUF);
#ifndef __FreeBSD__
	free(ahd, M_DEVBUF);
#endif
	return;
}