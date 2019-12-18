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
struct wreg_addr {int /*<<< orphan*/  chips; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E2 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3A0 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E3B0 (struct bxe_softc*) ; 
 int IS_E1H_REG (int /*<<< orphan*/ ) ; 
 int IS_E1_REG (int /*<<< orphan*/ ) ; 
 int IS_E2_REG (int /*<<< orphan*/ ) ; 
 int IS_E3A0_REG (int /*<<< orphan*/ ) ; 
 int IS_E3B0_REG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bxe_is_wreg_in_chip(struct bxe_softc *sc, const struct wreg_addr *wreg_info)
{
    if (CHIP_IS_E1(sc))
        return IS_E1_REG(wreg_info->chips);
    else if (CHIP_IS_E1H(sc))
        return IS_E1H_REG(wreg_info->chips);
    else if (CHIP_IS_E2(sc))
        return IS_E2_REG(wreg_info->chips);
    else if (CHIP_IS_E3A0(sc))
        return IS_E3A0_REG(wreg_info->chips);
    else if (CHIP_IS_E3B0(sc))
        return IS_E3B0_REG(wreg_info->chips);
    else
        return 0;
}