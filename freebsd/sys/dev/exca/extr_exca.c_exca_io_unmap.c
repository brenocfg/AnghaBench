#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct exca_softc {int ioalloc; TYPE_1__* io; } ;
struct TYPE_4__ {int /*<<< orphan*/  ioenable; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ flags; scalar_t__ size; scalar_t__ addr; scalar_t__ ioh; scalar_t__ iot; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXCA_ADDRWIN_ENABLE ; 
 int EXCA_IO_WINS ; 
 int /*<<< orphan*/  exca_clrb (struct exca_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* io_map_index ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
exca_io_unmap(struct exca_softc *sc, int window)
{
	if (window >= EXCA_IO_WINS)
		panic("exca_io_unmap: window out of range");

	exca_clrb(sc, EXCA_ADDRWIN_ENABLE, io_map_index[window].ioenable);

	sc->ioalloc &= ~(1 << window);

	sc->io[window].iot = 0;
	sc->io[window].ioh = 0;
	sc->io[window].addr = 0;
	sc->io[window].size = 0;
	sc->io[window].flags = 0;
	sc->io[window].width = 0;
}