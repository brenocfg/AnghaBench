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
struct dmae_cmd {int dummy; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int DMAE_REG_CMD_MEM ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int* dmae_reg_go_c ; 

void
bxe_post_dmae(struct bxe_softc    *sc,
              struct dmae_cmd *dmae,
              int                 idx)
{
    uint32_t cmd_offset;
    int i;

    cmd_offset = (DMAE_REG_CMD_MEM + (sizeof(struct dmae_cmd) * idx));
    for (i = 0; i < ((sizeof(struct dmae_cmd) / 4)); i++) {
        REG_WR(sc, (cmd_offset + (i * 4)), *(((uint32_t *)dmae) + i));
    }

    REG_WR(sc, dmae_reg_go_c[idx], 1);
}