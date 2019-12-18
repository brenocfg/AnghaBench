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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ MISC_REG_AEU_GENERAL_ATTN_12 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,int) ; 
 int SC_FUNC (struct bxe_softc*) ; 

void
elink_cb_notify_link_changed(struct bxe_softc *sc)
{
    REG_WR(sc, (MISC_REG_AEU_GENERAL_ATTN_12 +
                (SC_FUNC(sc) * sizeof(uint32_t))), 1);
}