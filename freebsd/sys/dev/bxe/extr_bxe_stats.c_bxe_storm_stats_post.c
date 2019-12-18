#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bxe_softc {int stats_pending; int /*<<< orphan*/  fw_stats_req_mapping; TYPE_1__* fw_stats_req; int /*<<< orphan*/  stats_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/  drv_stats_counter; } ;
struct TYPE_3__ {TYPE_2__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BXE_STATS_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_STATS_UNLOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_STATS ; 
 int /*<<< orphan*/  NONE_CONNECTION_TYPE ; 
 int /*<<< orphan*/  RAMROD_CMD_ID_COMMON_STAT_QUERY ; 
 int /*<<< orphan*/  U64_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_dp_stats (struct bxe_softc*) ; 
 int bxe_sp_post (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_storm_stats_post(struct bxe_softc *sc)
{
    int rc;

    if (!sc->stats_pending) {
        BXE_STATS_LOCK(sc);

        if (sc->stats_pending) {
            BXE_STATS_UNLOCK(sc);
            return;
        }

        sc->fw_stats_req->hdr.drv_stats_counter =
            htole16(sc->stats_counter++);

        BLOGD(sc, DBG_STATS,
              "sending statistics ramrod %d\n",
              le16toh(sc->fw_stats_req->hdr.drv_stats_counter));

        /* adjust the ramrod to include VF queues statistics */
        // XXX bxe_iov_adjust_stats_req(sc);

        bxe_dp_stats(sc);

        /* send FW stats ramrod */
        rc = bxe_sp_post(sc, RAMROD_CMD_ID_COMMON_STAT_QUERY, 0,
                         U64_HI(sc->fw_stats_req_mapping),
                         U64_LO(sc->fw_stats_req_mapping),
                         NONE_CONNECTION_TYPE);
        if (rc == 0) {
            sc->stats_pending = 1;
        }

        BXE_STATS_UNLOCK(sc);
    }
}