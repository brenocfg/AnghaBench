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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct sbbc_softc {int /*<<< orphan*/  sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 scalar_t__ SBBC_SRAM_READ_8 (scalar_t__) ; 
 scalar_t__ SBBC_TOD_OFF (int /*<<< orphan*/ ) ; 
 struct sbbc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ sbbc_toddata ; 
 int /*<<< orphan*/  tod_skew ; 
 int /*<<< orphan*/  tod_time ; 

__attribute__((used)) static int
sbbc_tod_gettime(device_t dev, struct timespec *ts)
{
	struct sbbc_softc *sc;
	bus_space_tag_t bst;
	bus_space_handle_t bsh;

	sc = device_get_softc(dev);
	bst = rman_get_bustag(sc->sc_res);
	bsh = rman_get_bushandle(sc->sc_res);

	ts->tv_sec = SBBC_SRAM_READ_8(sbbc_toddata + SBBC_TOD_OFF(tod_time)) +
	    SBBC_SRAM_READ_8(sbbc_toddata + SBBC_TOD_OFF(tod_skew));
	ts->tv_nsec = 0;
	return (0);
}