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
struct TYPE_2__ {int /*<<< orphan*/  driver_abi; int /*<<< orphan*/  driver_mtx; int /*<<< orphan*/  ppscap; } ;
struct uart_softc {TYPE_1__ sc_pps; int /*<<< orphan*/  sc_pps_mode; int /*<<< orphan*/  sc_dev; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;

/* Variables and functions */
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PPS_ABI_VERSION ; 
 int /*<<< orphan*/  PPS_CAPTUREBOTH ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct uart_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UART_PPS_CTS ; 
 int /*<<< orphan*/  UART_PPS_DCD ; 
 int /*<<< orphan*/  UART_PPS_DISABLED ; 
 scalar_t__ bootverbose ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pps_init_abi (TYPE_1__*) ; 
 int /*<<< orphan*/  uart_pps_mode_sysctl ; 
 int /*<<< orphan*/  uart_pps_mode_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_pps_print_mode (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_tty_getlock (struct uart_softc*) ; 

__attribute__((used)) static void
uart_pps_init(struct uart_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;

	ctx = device_get_sysctl_ctx(sc->sc_dev);
	tree = device_get_sysctl_tree(sc->sc_dev);

	/*
	 * The historical default for pps capture mode is either DCD or CTS,
	 * depending on the UART_PPS_ON_CTS kernel option.  Start with that,
	 * then try to fetch the tunable that overrides the mode for all uart
	 * devices, then try to fetch the sysctl-tunable that overrides the mode
	 * for one specific device.
	 */
#ifdef UART_PPS_ON_CTS
	sc->sc_pps_mode = UART_PPS_CTS;
#else
	sc->sc_pps_mode = UART_PPS_DCD;
#endif
	TUNABLE_INT_FETCH("hw.uart.pps_mode", &sc->sc_pps_mode);
	SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO, "pps_mode",
	    CTLTYPE_INT | CTLFLAG_RWTUN, sc, 0, uart_pps_mode_sysctl, "I",
	    "pulse mode: 0/1/2=disabled/CTS/DCD; "
	    "add 0x10 to invert, 0x20 for narrow pulse");

	if (!uart_pps_mode_valid(sc->sc_pps_mode)) {
		device_printf(sc->sc_dev, 
		    "Invalid pps_mode 0x%02x configured; disabling PPS capture\n",
		    sc->sc_pps_mode);
		sc->sc_pps_mode = UART_PPS_DISABLED;
	} else if (bootverbose) {
		uart_pps_print_mode(sc);
	}

	sc->sc_pps.ppscap = PPS_CAPTUREBOTH;
	sc->sc_pps.driver_mtx = uart_tty_getlock(sc);
	sc->sc_pps.driver_abi = PPS_ABI_VERSION;
	pps_init_abi(&sc->sc_pps);
}