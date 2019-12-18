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
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3 (struct bxe_softc*) ; 
 int /*<<< orphan*/  const* page_write_regs_e2 ; 
 int /*<<< orphan*/  const* page_write_regs_e3 ; 

__attribute__((used)) static const uint32_t *
__bxe_get_page_write_ar(struct bxe_softc *sc)
{
    if (CHIP_IS_E2(sc))
        return page_write_regs_e2;
    else if (CHIP_IS_E3(sc))
        return page_write_regs_e3;
    else
        return NULL;
}