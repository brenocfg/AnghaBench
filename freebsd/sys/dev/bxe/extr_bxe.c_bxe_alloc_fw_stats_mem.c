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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint8_t ;
struct stats_query_header {int dummy; } ;
struct stats_query_cmd_group {int dummy; } ;
struct stats_counter {int dummy; } ;
struct per_queue_stats {int dummy; } ;
struct per_port_stats {int dummy; } ;
struct per_pf_stats {int dummy; } ;
struct TYPE_2__ {scalar_t__ paddr; scalar_t__ vaddr; } ;
struct bxe_softc {int fw_stats_num; int fw_stats_req_size; int fw_stats_data_size; scalar_t__ fw_stats_data_mapping; scalar_t__ fw_stats_req_mapping; TYPE_1__ fw_stats_dma; struct bxe_fw_stats_data* fw_stats_data; struct bxe_fw_stats_req* fw_stats_req; } ;
struct bxe_fw_stats_req {int dummy; } ;
struct bxe_fw_stats_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,...) ; 
 int BXE_NUM_ETH_QUEUES (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int STATS_QUERY_CMD_COUNT ; 
 scalar_t__ bxe_dma_alloc (struct bxe_softc*,int,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  bxe_free_fw_stats_mem (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_alloc_fw_stats_mem(struct bxe_softc *sc)
{
    uint8_t num_queue_stats;
    int num_groups;

    /* number of queues for statistics is number of eth queues */
    num_queue_stats = BXE_NUM_ETH_QUEUES(sc);

    /*
     * Total number of FW statistics requests =
     *   1 for port stats + 1 for PF stats + num of queues
     */
    sc->fw_stats_num = (2 + num_queue_stats);

    /*
     * Request is built from stats_query_header and an array of
     * stats_query_cmd_group each of which contains STATS_QUERY_CMD_COUNT
     * rules. The real number or requests is configured in the
     * stats_query_header.
     */
    num_groups =
        ((sc->fw_stats_num / STATS_QUERY_CMD_COUNT) +
         ((sc->fw_stats_num % STATS_QUERY_CMD_COUNT) ? 1 : 0));

    BLOGD(sc, DBG_LOAD, "stats fw_stats_num %d num_groups %d\n",
          sc->fw_stats_num, num_groups);

    sc->fw_stats_req_size =
        (sizeof(struct stats_query_header) +
         (num_groups * sizeof(struct stats_query_cmd_group)));

    /*
     * Data for statistics requests + stats_counter.
     * stats_counter holds per-STORM counters that are incremented when
     * STORM has finished with the current request. Memory for FCoE
     * offloaded statistics are counted anyway, even if they will not be sent.
     * VF stats are not accounted for here as the data of VF stats is stored
     * in memory allocated by the VF, not here.
     */
    sc->fw_stats_data_size =
        (sizeof(struct stats_counter) +
         sizeof(struct per_port_stats) +
         sizeof(struct per_pf_stats) +
         /* sizeof(struct fcoe_statistics_params) + */
         (sizeof(struct per_queue_stats) * num_queue_stats));

    if (bxe_dma_alloc(sc, (sc->fw_stats_req_size + sc->fw_stats_data_size),
                      &sc->fw_stats_dma, "fw stats") != 0) {
        bxe_free_fw_stats_mem(sc);
        return (-1);
    }

    /* set up the shortcuts */

    sc->fw_stats_req =
        (struct bxe_fw_stats_req *)sc->fw_stats_dma.vaddr;
    sc->fw_stats_req_mapping = sc->fw_stats_dma.paddr;

    sc->fw_stats_data =
        (struct bxe_fw_stats_data *)((uint8_t *)sc->fw_stats_dma.vaddr +
                                     sc->fw_stats_req_size);
    sc->fw_stats_data_mapping = (sc->fw_stats_dma.paddr +
                                 sc->fw_stats_req_size);

    BLOGD(sc, DBG_LOAD, "statistics request base address set to %#jx\n",
          (uintmax_t)sc->fw_stats_req_mapping);

    BLOGD(sc, DBG_LOAD, "statistics data base address set to %#jx\n",
          (uintmax_t)sc->fw_stats_data_mapping);

    return (0);
}