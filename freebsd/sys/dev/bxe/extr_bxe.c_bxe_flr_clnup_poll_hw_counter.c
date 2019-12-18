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
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,char*,scalar_t__) ; 
 scalar_t__ bxe_flr_clnup_reg_poll (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
bxe_flr_clnup_poll_hw_counter(struct bxe_softc *sc,
                              uint32_t         reg,
                              char             *msg,
                              uint32_t         poll_cnt)
{
    uint32_t val = bxe_flr_clnup_reg_poll(sc, reg, 0, poll_cnt);

    if (val != 0) {
        BLOGE(sc, "%s usage count=%d\n", msg, val);
        return (1);
    }

    return (0);
}