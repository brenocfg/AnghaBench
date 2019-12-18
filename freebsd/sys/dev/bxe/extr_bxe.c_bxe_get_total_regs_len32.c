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
 int DUMP_MAX_PRESETS ; 
 scalar_t__ bxe_get_preset_regs_len (struct bxe_softc*,int) ; 

__attribute__((used)) static int
bxe_get_total_regs_len32(struct bxe_softc *sc)
{
    uint32_t preset_idx;
    int regdump_len32 = 0;


    /* Calculate the total preset regs length */
    for (preset_idx = 1; preset_idx <= DUMP_MAX_PRESETS; preset_idx++) {
        regdump_len32 += bxe_get_preset_regs_len(sc, preset_idx);
    }

    return regdump_len32;
}