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
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  cmng_enables; } ;
struct cmng_init_input {TYPE_2__ flags; int /*<<< orphan*/  port_rate; } ;
struct TYPE_4__ {scalar_t__ pmf; } ;
struct TYPE_6__ {int /*<<< orphan*/  line_speed; } ;
struct bxe_softc {int /*<<< orphan*/  cmng; TYPE_1__ port; TYPE_3__ link_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CMNG_FLAGS_PER_PORT_RATE_SHAPING_VN ; 
 scalar_t__ CMNG_FNS_MINMAX ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int SC_MAX_VN_NUM (struct bxe_softc*) ; 
 int VN_0 ; 
 int /*<<< orphan*/  bxe_calc_vn_max (struct bxe_softc*,int,struct cmng_init_input*) ; 
 int /*<<< orphan*/  bxe_calc_vn_min (struct bxe_softc*,struct cmng_init_input*) ; 
 int /*<<< orphan*/  bxe_read_mf_cfg (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_init_cmng (struct cmng_init_input*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct cmng_init_input*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bxe_cmng_fns_init(struct bxe_softc *sc,
                  uint8_t          read_cfg,
                  uint8_t          cmng_type)
{
    struct cmng_init_input input;
    int vn;

    memset(&input, 0, sizeof(struct cmng_init_input));

    input.port_rate = sc->link_vars.line_speed;

    if (cmng_type == CMNG_FNS_MINMAX) {
        /* read mf conf from shmem */
        if (read_cfg) {
            bxe_read_mf_cfg(sc);
        }

        /* get VN min rate and enable fairness if not 0 */
        bxe_calc_vn_min(sc, &input);

        /* get VN max rate */
        if (sc->port.pmf) {
            for (vn = VN_0; vn < SC_MAX_VN_NUM(sc); vn++) {
                bxe_calc_vn_max(sc, vn, &input);
            }
        }

        /* always enable rate shaping and fairness */
        input.flags.cmng_enables |= CMNG_FLAGS_PER_PORT_RATE_SHAPING_VN;

        ecore_init_cmng(&input, &sc->cmng);
        return;
    }

    /* rate shaping and fairness are disabled */
    BLOGD(sc, DBG_LOAD, "rate shaping and fairness have been disabled\n");
}