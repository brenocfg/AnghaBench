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
struct reg_addr {int size; int addr; int /*<<< orphan*/  presets; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_REG_IN_PRESET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int const,int const) ; 
 int* __bxe_get_page_addr_ar (struct bxe_softc*) ; 
 struct reg_addr* __bxe_get_page_read_ar (struct bxe_softc*) ; 
 int __bxe_get_page_read_num (struct bxe_softc*) ; 
 int __bxe_get_page_reg_num (struct bxe_softc*) ; 
 int* __bxe_get_page_write_ar (struct bxe_softc*) ; 
 int __bxe_get_page_write_num (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_read_pages_regs(struct bxe_softc *sc, uint32_t *p, uint32_t preset)
{
    uint32_t i, j, k, n;

    /* addresses of the paged registers */
    const uint32_t *page_addr = __bxe_get_page_addr_ar(sc);
    /* number of paged registers */
    int num_pages = __bxe_get_page_reg_num(sc);
    /* write addresses */
    const uint32_t *write_addr = __bxe_get_page_write_ar(sc);
    /* number of write addresses */
    int write_num = __bxe_get_page_write_num(sc);
    /* read addresses info */
    const struct reg_addr *read_addr = __bxe_get_page_read_ar(sc);
    /* number of read addresses */
    int read_num = __bxe_get_page_read_num(sc);
    uint32_t addr, size;

    for (i = 0; i < num_pages; i++) {
        for (j = 0; j < write_num; j++) {
            REG_WR(sc, write_addr[j], page_addr[i]);

            for (k = 0; k < read_num; k++) {
                if (IS_REG_IN_PRESET(read_addr[k].presets, preset)) {
                    size = read_addr[k].size;
                    for (n = 0; n < size; n++) {
                        addr = read_addr[k].addr + n*4;
                        *p++ = REG_RD(sc, addr);
                    }
                }
            }
        }
    }
    return;
}