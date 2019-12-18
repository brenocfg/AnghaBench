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
typedef  scalar_t__ uint8_t ;
struct bxe_softc {int flags; } ;
struct bxe_fastpath {int dummy; } ;

/* Variables and functions */
 int BXE_TX_SWITCHING ; 
 int /*<<< orphan*/  ECORE_Q_FLG_ACTIVE ; 
 int /*<<< orphan*/  ECORE_Q_FLG_PCSUM_ON_PKT ; 
 int /*<<< orphan*/  ECORE_Q_FLG_STATS ; 
 int /*<<< orphan*/  ECORE_Q_FLG_TX_SWITCH ; 
 int /*<<< orphan*/  ECORE_Q_FLG_ZERO_STATS ; 
 int /*<<< orphan*/  bxe_set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static unsigned long
bxe_get_common_flags(struct bxe_softc    *sc,
                     struct bxe_fastpath *fp,
                     uint8_t             zero_stats)
{
    unsigned long flags = 0;

    /* PF driver will always initialize the Queue to an ACTIVE state */
    bxe_set_bit(ECORE_Q_FLG_ACTIVE, &flags);

    /*
     * tx only connections collect statistics (on the same index as the
     * parent connection). The statistics are zeroed when the parent
     * connection is initialized.
     */

    bxe_set_bit(ECORE_Q_FLG_STATS, &flags);
    if (zero_stats) {
        bxe_set_bit(ECORE_Q_FLG_ZERO_STATS, &flags);
    }

    /*
     * tx only connections can support tx-switching, though their
     * CoS-ness doesn't survive the loopback
     */
    if (sc->flags & BXE_TX_SWITCHING) {
        bxe_set_bit(ECORE_Q_FLG_TX_SWITCH, &flags);
    }

    bxe_set_bit(ECORE_Q_FLG_PCSUM_ON_PKT, &flags);

    return (flags);
}