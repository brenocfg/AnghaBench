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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_CSTRORM_INTMEM ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CSTORM_STATUS_BLOCK_DATA_TIMEOUT_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  REG_WR8 (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_storm_memset_hc_timeout(struct bxe_softc *sc,
                            uint8_t          port,
                            uint8_t          fw_sb_id,
                            uint8_t          sb_index,
                            uint8_t          ticks)
{
    uint32_t addr =
        (BAR_CSTRORM_INTMEM +
         CSTORM_STATUS_BLOCK_DATA_TIMEOUT_OFFSET(fw_sb_id, sb_index));

    REG_WR8(sc, addr, ticks);

    BLOGD(sc, DBG_LOAD,
          "port %d fw_sb_id %d sb_index %d ticks %d\n",
          port, fw_sb_id, sb_index, ticks);
}