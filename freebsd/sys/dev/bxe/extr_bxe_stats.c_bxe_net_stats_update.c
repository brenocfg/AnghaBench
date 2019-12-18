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
struct bxe_softc {int num_queues; TYPE_2__* fp; int /*<<< orphan*/  ifp; } ;
struct TYPE_3__ {int /*<<< orphan*/  checksum_discard; } ;
struct TYPE_4__ {TYPE_1__ old_tclient; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_net_stats_update(struct bxe_softc *sc)
{

    for (int i = 0; i < sc->num_queues; i++)
        if_inc_counter(sc->ifp, IFCOUNTER_IQDROPS,
	    le32toh(sc->fp[i].old_tclient.checksum_discard));
}