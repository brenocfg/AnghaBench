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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sbni_softc {scalar_t__ io_off; int /*<<< orphan*/  io_res; } ;

/* Variables and functions */
 scalar_t__ DAT ; 
 int /*<<< orphan*/  bus_space_write_multi_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
sbni_outsb(struct sbni_softc *sc, u_char *from, u_int len)
{
	bus_space_write_multi_1(
	    rman_get_bustag(sc->io_res),
	    rman_get_bushandle(sc->io_res),
	    sc->io_off + DAT, from, len);
}