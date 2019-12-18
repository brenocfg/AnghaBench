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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,scalar_t__) ; 

void
ecore_storm_memset_struct(struct bxe_softc *sc,
                          uint32_t         addr,
                          size_t           size,
                          uint32_t         *data)
{
    uint8_t i;
    for (i = 0; i < size/4; i++) {
        REG_WR(sc, addr + (i * 4), data[i]);
    }
}