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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ NIG_REG_LLH0_FUNC_EN ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_tx_disable (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_e1h_disable(struct bxe_softc *sc)
{
    int port = SC_PORT(sc);

    bxe_tx_disable(sc);

    REG_WR(sc, NIG_REG_LLH0_FUNC_EN + port*8, 0);
}