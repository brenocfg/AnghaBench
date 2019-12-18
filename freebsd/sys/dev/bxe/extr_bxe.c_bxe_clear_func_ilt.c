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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ FUNC_ILT_BASE (scalar_t__) ; 
 scalar_t__ ILT_PER_FUNC ; 
 int /*<<< orphan*/  bxe_ilt_wr (struct bxe_softc*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_clear_func_ilt(struct bxe_softc *sc,
                   uint32_t         func)
{
    uint32_t i, base = FUNC_ILT_BASE(func);
    for (i = base; i < base + ILT_PER_FUNC; i++) {
        bxe_ilt_wr(sc, i, 0);
    }
}