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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_REV_IS_EMUL (struct bxe_softc*) ; 
 scalar_t__ CHIP_REV_IS_FPGA (struct bxe_softc*) ; 
 int FLR_POLL_CNT ; 

__attribute__((used)) static uint32_t
bxe_flr_clnup_poll_count(struct bxe_softc *sc)
{
    /* adjust polling timeout */
    if (CHIP_REV_IS_EMUL(sc)) {
        return (FLR_POLL_CNT * 2000);
    }

    if (CHIP_REV_IS_FPGA(sc)) {
        return (FLR_POLL_CNT * 120);
    }

    return (FLR_POLL_CNT);
}