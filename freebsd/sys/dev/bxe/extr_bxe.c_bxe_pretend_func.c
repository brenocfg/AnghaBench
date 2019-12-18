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
typedef  int /*<<< orphan*/  uint16_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 int /*<<< orphan*/  E1H_FUNC_MAX ; 
 int /*<<< orphan*/  REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_get_pretend_reg (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_pretend_func(struct bxe_softc *sc,
                 uint16_t         pretend_func_val)
{
    uint32_t pretend_reg;

    if (CHIP_IS_E1H(sc) && (pretend_func_val > E1H_FUNC_MAX)) {
        return (-1);
    }

    /* get my own pretend register */
    pretend_reg = bxe_get_pretend_reg(sc);
    REG_WR(sc, pretend_reg, pretend_func_val);
    REG_RD(sc, pretend_reg);
    return (0);
}