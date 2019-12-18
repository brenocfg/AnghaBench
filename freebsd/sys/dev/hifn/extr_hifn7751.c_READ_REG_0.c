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
typedef  int /*<<< orphan*/  u_int32_t ;
struct hifn_softc {scalar_t__ sc_bar0_lastreg; int /*<<< orphan*/  sc_sh0; int /*<<< orphan*/  sc_st0; } ;
typedef  scalar_t__ bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __inline u_int32_t
READ_REG_0(struct hifn_softc *sc, bus_size_t reg)
{
    u_int32_t v = bus_space_read_4(sc->sc_st0, sc->sc_sh0, reg);
    sc->sc_bar0_lastreg = (bus_size_t) -1;
    return (v);
}