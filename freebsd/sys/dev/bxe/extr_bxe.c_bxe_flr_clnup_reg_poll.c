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
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLR_WAIT_INTERVAL ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
bxe_flr_clnup_reg_poll(struct bxe_softc *sc,
                       uint32_t         reg,
                       uint32_t         expected,
                       uint32_t         poll_count)
{
    uint32_t cur_cnt = poll_count;
    uint32_t val;

    while ((val = REG_RD(sc, reg)) != expected && cur_cnt--) {
        DELAY(FLR_WAIT_INTERVAL);
    }

    return (val);
}