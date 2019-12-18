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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int BXE_PATH0_RST_IN_PROG_BIT ; 
 int BXE_PATH1_RST_IN_PROG_BIT ; 
 int /*<<< orphan*/  BXE_RECOVERY_GLOB_REG ; 
 int /*<<< orphan*/  FALSE ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static uint8_t
bxe_reset_is_done(struct bxe_softc *sc,
                  int              engine)
{
    uint32_t val = REG_RD(sc, BXE_RECOVERY_GLOB_REG);
    uint32_t bit = engine ? BXE_PATH1_RST_IN_PROG_BIT :
                            BXE_PATH0_RST_IN_PROG_BIT;

    /* return false if bit is set */
    return (val & bit) ? FALSE : TRUE;
}