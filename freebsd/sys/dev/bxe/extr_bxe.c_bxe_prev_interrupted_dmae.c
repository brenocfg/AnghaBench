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
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int PGLUE_B_PGLUE_B_INT_STS_REG_WAS_ERROR_ATTN ; 
 int /*<<< orphan*/  PGLUE_B_REG_PGLUE_B_INT_STS ; 
 int /*<<< orphan*/  PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR ; 
 int REG_RD (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 
 int SC_FUNC (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_prev_interrupted_dmae(struct bxe_softc *sc)
{
    uint32_t val;

    if (!CHIP_IS_E1x(sc)) {
        val = REG_RD(sc, PGLUE_B_REG_PGLUE_B_INT_STS);
        if (val & PGLUE_B_PGLUE_B_INT_STS_REG_WAS_ERROR_ATTN) {
            BLOGD(sc, DBG_LOAD,
                  "Clearing 'was-error' bit that was set in pglueb");
            REG_WR(sc, PGLUE_B_REG_WAS_ERROR_PF_7_0_CLR, 1 << SC_FUNC(sc));
        }
    }
}