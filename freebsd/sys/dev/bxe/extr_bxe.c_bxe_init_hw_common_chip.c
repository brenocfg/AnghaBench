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
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int) ; 
 int /*<<< orphan*/  BXE_NOMCP (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_common_init_phy (struct bxe_softc*) ; 
 int bxe_init_hw_common (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_init_hw_common_chip(struct bxe_softc *sc)
{
    int rc = bxe_init_hw_common(sc);

    if (rc) {
        BLOGE(sc, "bxe_init_hw_common failed rc=%d\n", rc);
        return (rc);
    }

    /* In E2 2-PORT mode, same ext phy is used for the two paths */
    if (!BXE_NOMCP(sc)) {
        bxe_common_init_phy(sc);
    }

    return (0);
}