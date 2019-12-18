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
struct bxe_softc {int /*<<< orphan*/  iro_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 scalar_t__ CHIP_IS_E1 (struct bxe_softc*) ; 
 scalar_t__ CHIP_IS_E1H (struct bxe_softc*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  e1_iro_arr ; 
 int /*<<< orphan*/  e1h_iro_arr ; 
 int /*<<< orphan*/  e2_iro_arr ; 
 int /*<<< orphan*/  ecore_init_e1_firmware (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_init_e1h_firmware (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_init_e2_firmware (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_init_firmware(struct bxe_softc *sc)
{
    if (CHIP_IS_E1(sc)) {
        ecore_init_e1_firmware(sc);
        sc->iro_array = e1_iro_arr;
    } else if (CHIP_IS_E1H(sc)) {
        ecore_init_e1h_firmware(sc);
        sc->iro_array = e1h_iro_arr;
    } else if (!CHIP_IS_E1x(sc)) {
        ecore_init_e2_firmware(sc);
        sc->iro_array = e2_iro_arr;
    } else {
        BLOGE(sc, "Unsupported chip revision\n");
        return (-1);
    }

    return (0);
}