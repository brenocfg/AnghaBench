#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  struct fman_softc* t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct fman_softc {TYPE_1__ sc_base; } ;
typedef  int /*<<< orphan*/  e_FmPortType ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
fman_error_callback(t_Handle app_handle, e_FmPortType port_type,
    uint8_t port_id, uint64_t addr, uint8_t tnum, uint16_t liodn)
{
	struct fman_softc *sc;

	sc = app_handle;
	device_printf(sc->sc_base.dev, "FMan error occurred.\n");
}