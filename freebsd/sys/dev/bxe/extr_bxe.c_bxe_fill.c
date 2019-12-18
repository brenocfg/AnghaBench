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
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int /*<<< orphan*/  REG_WR8 (struct bxe_softc*,int,int) ; 

__attribute__((used)) static void
bxe_fill(struct bxe_softc *sc,
         uint32_t         addr,
         int              fill,
         uint32_t         len)
{
    uint32_t i;

    if (!(len % 4) && !(addr % 4)) {
        for (i = 0; i < len; i += 4) {
            REG_WR(sc, (addr + i), fill);
        }
    } else {
        for (i = 0; i < len; i++) {
            REG_WR8(sc, (addr + i), fill);
        }
    }
}