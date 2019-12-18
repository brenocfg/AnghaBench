#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bxe_softc {TYPE_5__* fw_stats_req; } ;
struct TYPE_6__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_7__ {int cmd_num; TYPE_1__ stats_counters_addrs; int /*<<< orphan*/  reserved1; int /*<<< orphan*/  drv_stats_counter; int /*<<< orphan*/  reserved0; } ;
struct TYPE_10__ {TYPE_4__* query; TYPE_2__ hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_9__ {TYPE_3__ address; int /*<<< orphan*/  reserved; int /*<<< orphan*/  funcID; int /*<<< orphan*/  index; int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBG_STATS ; 

__attribute__((used)) static void
bxe_dp_stats(struct bxe_softc *sc)
{
    int i;

    BLOGD(sc, DBG_STATS,
          "dumping stats:\n"
          "  fw_stats_req\n"
          "    hdr\n"
          "      cmd_num %d\n"
          "      reserved0 %d\n"
          "      drv_stats_counter %d\n"
          "      reserved1 %d\n"
          "      stats_counters_addrs %x %x\n",
          sc->fw_stats_req->hdr.cmd_num,
          sc->fw_stats_req->hdr.reserved0,
          sc->fw_stats_req->hdr.drv_stats_counter,
          sc->fw_stats_req->hdr.reserved1,
          sc->fw_stats_req->hdr.stats_counters_addrs.hi,
          sc->fw_stats_req->hdr.stats_counters_addrs.lo);

    for (i = 0; i < sc->fw_stats_req->hdr.cmd_num; i++) {
        BLOGD(sc, DBG_STATS,
              "query[%d]\n"
              "  kind %d\n"
              "  index %d\n"
              "  funcID %d\n"
              "  reserved %d\n"
              "  address %x %x\n",
              i,
              sc->fw_stats_req->query[i].kind,
              sc->fw_stats_req->query[i].index,
              sc->fw_stats_req->query[i].funcID,
              sc->fw_stats_req->query[i].reserved,
              sc->fw_stats_req->query[i].address.hi,
              sc->fw_stats_req->query[i].address.lo);
    }
}