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
struct bxe_softc {scalar_t__ fw_stats_data_mapping; int /*<<< orphan*/ * fw_stats_data; scalar_t__ fw_stats_data_size; scalar_t__ fw_stats_req_mapping; int /*<<< orphan*/ * fw_stats_req; scalar_t__ fw_stats_req_size; scalar_t__ fw_stats_num; int /*<<< orphan*/  fw_stats_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxe_dma_free (struct bxe_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_free_fw_stats_mem(struct bxe_softc *sc)
{
    bxe_dma_free(sc, &sc->fw_stats_dma);

    sc->fw_stats_num = 0;

    sc->fw_stats_req_size = 0;
    sc->fw_stats_req = NULL;
    sc->fw_stats_req_mapping = 0;

    sc->fw_stats_data_size = 0;
    sc->fw_stats_data = NULL;
    sc->fw_stats_data_mapping = 0;
}