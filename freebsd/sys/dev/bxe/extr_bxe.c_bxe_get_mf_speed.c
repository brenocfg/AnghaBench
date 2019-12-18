#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/ * mf_config; } ;
struct TYPE_6__ {TYPE_2__ mf_info; } ;
struct TYPE_4__ {int line_speed; } ;
struct bxe_softc {TYPE_3__ devinfo; TYPE_1__ link_vars; } ;

/* Variables and functions */
 scalar_t__ IS_MF (struct bxe_softc*) ; 
 scalar_t__ IS_MF_SI (struct bxe_softc*) ; 
 size_t SC_VN (struct bxe_softc*) ; 
 int bxe_extract_max_cfg (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
bxe_get_mf_speed(struct bxe_softc *sc)
{
    uint16_t line_speed = sc->link_vars.line_speed;
    if (IS_MF(sc)) {
        uint16_t maxCfg =
            bxe_extract_max_cfg(sc, sc->devinfo.mf_info.mf_config[SC_VN(sc)]);

        /* calculate the current MAX line speed limit for the MF devices */
        if (IS_MF_SI(sc)) {
            line_speed = (line_speed * maxCfg) / 100;
        } else { /* SD mode */
            uint16_t vn_max_rate = maxCfg * 100;

            if (vn_max_rate < line_speed) {
                line_speed = vn_max_rate;
            }
        }
    }

    return (line_speed);
}