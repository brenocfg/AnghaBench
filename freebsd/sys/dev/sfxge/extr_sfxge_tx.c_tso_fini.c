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
struct sfxge_txq {int /*<<< orphan*/ * tsoh_buffer; TYPE_1__* sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  txq_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SFXGE ; 
 int TSOH_PAGE_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_dma_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tso_fini(struct sfxge_txq *txq)
{
	int i;

	if (txq->tsoh_buffer != NULL) {
		for (i = 0; i < TSOH_PAGE_COUNT(txq->sc->txq_entries); i++)
			sfxge_dma_free(&txq->tsoh_buffer[i]);
		free(txq->tsoh_buffer, M_SFXGE);
	}
}