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
typedef  int u_int ;
struct TYPE_3__ {int eax; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry; TYPE_1__ r; int /*<<< orphan*/  seg; } ;
struct apm_softc {int bios_busy; scalar_t__ connectmode; TYPE_2__ bios; int /*<<< orphan*/  minorversion; int /*<<< orphan*/  majorversion; int /*<<< orphan*/  intversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_DPRINT (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ APM_PROT32CONNECT ; 
 int BIOSCODE_FLAG ; 
 int BIOSDATA_FLAG ; 
 int /*<<< orphan*/  GBIOSCODE32_SEL ; 
 int /*<<< orphan*/  GSEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEL_KPL ; 
 int /*<<< orphan*/  apm_check_function_supported (int /*<<< orphan*/ ,int) ; 
 struct apm_softc apm_softc ; 
 int bios16 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int bios32 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bios_selectors (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
apm_bioscall(void)
{
	struct apm_softc *sc = &apm_softc;
	int errno = 0;
	u_int apm_func = sc->bios.r.eax & 0xff;

	if (!apm_check_function_supported(sc->intversion, apm_func)) {
		APM_DPRINT("apm_bioscall: function 0x%x is not supported in v%d.%d\n",
		    apm_func, sc->majorversion, sc->minorversion);
		return (-1);
	}

	sc->bios_busy = 1;
	if (sc->connectmode == APM_PROT32CONNECT) {
		set_bios_selectors(&sc->bios.seg,
				   BIOSCODE_FLAG | BIOSDATA_FLAG);
		errno = bios32(&sc->bios.r,
			       sc->bios.entry, GSEL(GBIOSCODE32_SEL, SEL_KPL));
	} else {
		errno = bios16(&sc->bios, NULL);
	}
	sc->bios_busy = 0;
	return (errno);
}