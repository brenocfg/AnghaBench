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
struct atibl_softc {int /*<<< orphan*/  sc_level; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  atibl_getlevel (struct atibl_softc*) ; 
 int /*<<< orphan*/  atibl_setlevel (struct atibl_softc*,int /*<<< orphan*/ ) ; 
 struct atibl_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atibl_suspend(device_t dev)
{
	struct atibl_softc *sc;

	sc = device_get_softc(dev);

	sc->sc_level = atibl_getlevel(sc);
	atibl_setlevel(sc, 0);

	return (0);
}