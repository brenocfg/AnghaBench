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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int pfunc_rel; int path_id; int pfunc_abs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAR_ME_REGISTER ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 scalar_t__ CHIP_4_PORT_MODE ; 
 scalar_t__ CHIP_PORT_MODE (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int ME_REG_ABS_PF_NUM ; 
 int ME_REG_ABS_PF_NUM_SHIFT ; 
 int ME_REG_PF_NUM ; 
 int ME_REG_PF_NUM_SHIFT ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_get_function_num(struct bxe_softc *sc)
{
    uint32_t val = 0;

    /*
     * Read the ME register to get the function number. The ME register
     * holds the relative-function number and absolute-function number. The
     * absolute-function number appears only in E2 and above. Before that
     * these bits always contained zero, therefore we cannot blindly use them.
     */

    val = REG_RD(sc, BAR_ME_REGISTER);

    sc->pfunc_rel =
        (uint8_t)((val & ME_REG_PF_NUM) >> ME_REG_PF_NUM_SHIFT);
    sc->path_id =
        (uint8_t)((val & ME_REG_ABS_PF_NUM) >> ME_REG_ABS_PF_NUM_SHIFT) & 1;

    if (CHIP_PORT_MODE(sc) == CHIP_4_PORT_MODE) {
        sc->pfunc_abs = ((sc->pfunc_rel << 1) | sc->path_id);
    } else {
        sc->pfunc_abs = (sc->pfunc_rel | sc->path_id);
    }

    BLOGD(sc, DBG_LOAD,
          "Relative function %d, Absolute function %d, Path %d\n",
          sc->pfunc_rel, sc->pfunc_abs, sc->path_id);
}