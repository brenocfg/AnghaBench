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
typedef  int uint16_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int FUNC_MF_CFG_MAX_BW_MASK ; 
 int FUNC_MF_CFG_MAX_BW_SHIFT ; 

__attribute__((used)) static inline uint16_t
bxe_extract_max_cfg(struct bxe_softc *sc,
                    uint32_t         mf_cfg)
{
    uint16_t max_cfg = ((mf_cfg & FUNC_MF_CFG_MAX_BW_MASK) >>
                        FUNC_MF_CFG_MAX_BW_SHIFT);

    if (!max_cfg) {
        BLOGD(sc, DBG_LOAD, "Max BW configured to 0 - using 100 instead\n");
        max_cfg = 100;
    }

    return (max_cfg);
}