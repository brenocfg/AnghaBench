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
typedef  scalar_t__ uint64_t ;
struct schizo_softc {scalar_t__ sc_mode; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 scalar_t__ SCHIZO_CTRL_READ_8 (struct schizo_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ SCHIZO_MODE_TOM ; 
 int /*<<< orphan*/  STX_CTRL_BUS_ERRLOG ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,char*,unsigned long long) ; 

__attribute__((used)) static int
schizo_host_bus(void *arg)
{
	struct schizo_softc *sc = arg;
	uint64_t errlog;

	errlog = SCHIZO_CTRL_READ_8(sc, STX_CTRL_BUS_ERRLOG);
	panic("%s: %s error %#llx", device_get_nameunit(sc->sc_dev),
	    sc->sc_mode == SCHIZO_MODE_TOM ? "JBus" : "Safari",
	    (unsigned long long)errlog);
	return (FILTER_HANDLED);
}