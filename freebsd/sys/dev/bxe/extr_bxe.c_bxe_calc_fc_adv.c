#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {int* advertising; } ;
struct TYPE_3__ {int ieee_fc; } ;
struct bxe_softc {TYPE_2__ port; TYPE_1__ link_vars; } ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
#define  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC 129 
#define  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH 128 
 int MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK ; 
 size_t bxe_get_link_cfg_idx (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_calc_fc_adv(struct bxe_softc *sc)
{
    uint8_t cfg_idx = bxe_get_link_cfg_idx(sc);


    sc->port.advertising[cfg_idx] &= ~(ADVERTISED_Asym_Pause |
                                           ADVERTISED_Pause);

    switch (sc->link_vars.ieee_fc &
            MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK) {

    case MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH:
        sc->port.advertising[cfg_idx] |= (ADVERTISED_Asym_Pause |
                                          ADVERTISED_Pause);
        break;

    case MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC:
        sc->port.advertising[cfg_idx] |= ADVERTISED_Asym_Pause;
        break;

    default:
        break;

    }
}