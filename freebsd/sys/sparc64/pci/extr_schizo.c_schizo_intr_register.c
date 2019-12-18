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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct schizo_softc {int /*<<< orphan*/  sc_ign; int /*<<< orphan*/  sc_dev; } ;
struct schizo_icarg {void* sica_clr; void* sica_map; struct schizo_softc* sica_sc; } ;
typedef  void* bus_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTMAP_VEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ SCHIZO_PCI_READ_8 (struct schizo_softc*,void*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct schizo_icarg*,int /*<<< orphan*/ ) ; 
 int intr_controller_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct schizo_icarg*) ; 
 struct schizo_icarg* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ schizo_get_intrmap (struct schizo_softc*,int /*<<< orphan*/ ,void**,void**) ; 
 int /*<<< orphan*/  schizo_ic ; 

__attribute__((used)) static int
schizo_intr_register(struct schizo_softc *sc, u_int ino)
{
	struct schizo_icarg *sica;
	bus_addr_t intrclr, intrmap;
	int error;

	if (schizo_get_intrmap(sc, ino, &intrmap, &intrclr) == 0)
		return (ENXIO);
	sica = malloc(sizeof(*sica), M_DEVBUF, M_NOWAIT);
	if (sica == NULL)
		return (ENOMEM);
	sica->sica_sc = sc;
	sica->sica_map = intrmap;
	sica->sica_clr = intrclr;
#ifdef SCHIZO_DEBUG
	device_printf(sc->sc_dev, "intr map (INO %d) %#lx: %#lx, clr: %#lx\n",
	    ino, (u_long)intrmap, (u_long)SCHIZO_PCI_READ_8(sc, intrmap),
	    (u_long)intrclr);
#endif
	error = (intr_controller_register(INTMAP_VEC(sc->sc_ign, ino),
	    &schizo_ic, sica));
	if (error != 0)
		free(sica, M_DEVBUF);
	return (error);
}