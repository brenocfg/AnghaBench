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
typedef  int /*<<< orphan*/  uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E1 (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_clp_reset_done (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int bxe_init_shmem (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_reset_mcp_comp(struct bxe_softc *sc,
                   uint32_t         magic_val)
{
    int rc = bxe_init_shmem(sc);

    /* Restore the `magic' bit value */
    if (!CHIP_IS_E1(sc)) {
        bxe_clp_reset_done(sc, magic_val);
    }

    return (rc);
}