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
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int DMAE_LEN32_WR_MAX (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_write_dmae (struct bxe_softc*,scalar_t__,int,int) ; 

void
bxe_write_dmae_phys_len(struct bxe_softc *sc,
                        bus_addr_t       phys_addr,
                        uint32_t         addr,
                        uint32_t         len)
{
    int dmae_wr_max = DMAE_LEN32_WR_MAX(sc);
    int offset = 0;

    while (len > dmae_wr_max) {
        bxe_write_dmae(sc,
                       (phys_addr + offset), /* src DMA address */
                       (addr + offset),      /* dst GRC address */
                       dmae_wr_max);
        offset += (dmae_wr_max * 4);
        len -= dmae_wr_max;
    }

    bxe_write_dmae(sc,
                   (phys_addr + offset), /* src DMA address */
                   (addr + offset),      /* dst GRC address */
                   len);
}