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
struct iwn_softc {int /*<<< orphan*/  txchainmask; } ;

/* Variables and functions */
 int IWN_LSB (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwn_get_1stream_tx_antmask(struct iwn_softc *sc)
{

	return IWN_LSB(sc->txchainmask);
}