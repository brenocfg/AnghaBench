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
typedef  int /*<<< orphan*/  uint64_t ;
struct mbuf {int dummy; } ;
struct ath_softc {int dummy; } ;
struct ath_rx_status {int dummy; } ;

/* Variables and functions */

void
ath_dfs_process_phy_err(struct ath_softc *sc, struct mbuf *m,
    uint64_t tsf, struct ath_rx_status *rxstat)
{

}