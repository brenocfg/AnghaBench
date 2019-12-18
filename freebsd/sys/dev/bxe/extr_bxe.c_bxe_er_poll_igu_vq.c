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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,scalar_t__) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  IGU_REG_PENDING_BITS_STATUS ; 
 scalar_t__ REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_er_poll_igu_vq(struct bxe_softc *sc)
{
    uint32_t cnt = 1000;
    uint32_t pend_bits = 0;

    do {
        pend_bits = REG_RD(sc, IGU_REG_PENDING_BITS_STATUS);

        if (pend_bits == 0) {
            break;
        }

        DELAY(1000);
    } while (--cnt > 0);

    if (cnt == 0) {
        BLOGE(sc, "Still pending IGU requests bits=0x%08x!\n", pend_bits);
        return (-1);
    }

    return (0);
}