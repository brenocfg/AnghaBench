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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_storm_memset_hc_disable (struct bxe_softc*,int,int,int,int) ; 
 int /*<<< orphan*/  bxe_storm_memset_hc_timeout (struct bxe_softc*,int,int,int,int) ; 

void
bxe_update_coalesce_sb_index(struct bxe_softc *sc,
                             uint8_t          fw_sb_id,
                             uint8_t          sb_index,
                             uint8_t          disable,
                             uint16_t         usec)
{
    int port = SC_PORT(sc);
    uint8_t ticks = (usec / 4); /* XXX ??? */

    bxe_storm_memset_hc_timeout(sc, port, fw_sb_id, sb_index, ticks);

    disable = (disable) ? 1 : ((usec) ? 0 : 1);
    bxe_storm_memset_hc_disable(sc, port, fw_sb_id, sb_index, disable);
}