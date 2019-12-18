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
typedef  int uint8_t ;
struct wb_softc {int chip; int ctl_reg; int time_reg; int csr_reg; int reg_1; int reg_timeout; int reg_2; unsigned long timeout_override; int /*<<< orphan*/  ev_tag; int /*<<< orphan*/  debug_verbose; int /*<<< orphan*/  dev; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLFLAG_SKIP ; 
 int CTLTYPE_INT ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct wb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,unsigned long*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 scalar_t__ TUNABLE_ULONG_FETCH (char*,unsigned long*) ; 
 int /*<<< orphan*/  WB_LDN8_CR30_ACTIVE ; 
 int WB_LDN8_CRF5_KBRST ; 
 int WB_LDN8_CRF5_KEYB_P20 ; 
 int WB_LDN8_CRF7_MOUSE ; 
 int WB_LDN8_CRF7_TS ; 
 scalar_t__ bootverbose ; 
 struct wb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
#define  nct6102 148 
#define  nct6775 147 
#define  nct6776 146 
#define  nct6779 145 
#define  nct6791 144 
#define  nct6792 143 
#define  nct6793 142 
#define  nct6795 141 
 int /*<<< orphan*/  superio_dev_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int superio_read (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  superio_write (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sysctl_wb_debug ; 
 int /*<<< orphan*/  sysctl_wb_debug_current ; 
 int /*<<< orphan*/  sysctl_wb_force_test_nmi ; 
#define  w83627dhg 140 
#define  w83627dhg_p 139 
#define  w83627ehf 138 
#define  w83627hf 137 
#define  w83627s 136 
#define  w83627thf 135 
#define  w83627uhg 134 
#define  w83637hf 133 
#define  w83667hg 132 
#define  w83667hg_b 131 
#define  w83687thf 130 
#define  w83697hf 129 
#define  w83697ug 128 
 int /*<<< orphan*/  watchdog_list ; 
 int /*<<< orphan*/  wb_print_state (struct wb_softc*,char*) ; 
 int /*<<< orphan*/  wb_watchdog_fn ; 

__attribute__((used)) static int
wb_attach(device_t dev)
{
	struct wb_softc *sc;
	struct sysctl_ctx_list *sctx;
	struct sysctl_oid *soid;
	unsigned long timeout;
	uint8_t t;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Make sure WDT is enabled. */
	superio_dev_enable(dev, WB_LDN8_CR30_ACTIVE);

	switch (sc->chip) {
	case w83697hf:
	case w83697ug:
		sc->ctl_reg = 0xf3;
		sc->time_reg = 0xf4;
		sc->csr_reg = 0xf7;
		break;
	case nct6102:
		sc->ctl_reg = 0xf0;
		sc->time_reg = 0xf1;
		sc->csr_reg = 0xf2;
		break;
	default:
		sc->ctl_reg = 0xf5;
		sc->time_reg = 0xf6;
		sc->csr_reg = 0xf7;
		break;
	}

	switch (sc->chip) {
	case w83627hf:
	case w83627s:
		t = superio_read(dev, 0x2B) & ~0x10;
		superio_write(dev, 0x2B, t); /* set GPIO24 to WDT0 */
		break;
	case w83697hf:
		/* Set pin 119 to WDTO# mode (= CR29, WDT0) */
		t = superio_read(dev, 0x29) & ~0x60;
		t |= 0x20;
		superio_write(dev, 0x29, t);
		break;
	case w83697ug:
		/* Set pin 118 to WDTO# mode */
		t = superio_read(dev, 0x2b) & ~0x04;
		superio_write(dev, 0x2b, t);
		break;
	case w83627thf:
		t = (superio_read(dev, 0x2B) & ~0x08) | 0x04;
		superio_write(dev, 0x2B, t); /* set GPIO3 to WDT0 */
		break;
	case w83627dhg:
	case w83627dhg_p:
		t = superio_read(dev, 0x2D) & ~0x01; /* PIN77 -> WDT0# */
		superio_write(dev, 0x2D, t); /* set GPIO5 to WDT0 */
		t = superio_read(dev, sc->ctl_reg);
		t |= 0x02;	/* enable the WDTO# output low pulse
				 * to the KBRST# pin */
		superio_write(dev, sc->ctl_reg, t);
		break;
	case w83637hf:
		break;
	case w83687thf:
		t = superio_read(dev, 0x2C) & ~0x80; /* PIN47 -> WDT0# */
		superio_write(dev, 0x2C, t);
		break;
	case w83627ehf:
	case w83627uhg:
	case w83667hg:
	case w83667hg_b:
	case nct6775:
	case nct6776:
	case nct6779:
	case nct6791:
	case nct6792:
	case nct6793:
	case nct6795:
	case nct6102:
		/*
		 * These chips have a fixed WDTO# output pin (W83627UHG),
		 * or support more than one WDTO# output pin.
		 * Don't touch its configuration, and hope the BIOS
		 * does the right thing.
		 */
		t = superio_read(dev, sc->ctl_reg);
		t |= 0x02;	/* enable the WDTO# output low pulse
				 * to the KBRST# pin */
		superio_write(dev, sc->ctl_reg, t);
		break;
	default:
		break;
	}

	/* Read the current watchdog configuration. */
	sc->reg_1 = superio_read(dev, sc->ctl_reg);
	sc->reg_timeout = superio_read(dev, sc->time_reg);
	sc->reg_2 = superio_read(dev, sc->csr_reg);

	/* Print current state if bootverbose or watchdog already enabled. */
	if (bootverbose || (sc->reg_timeout > 0x00))
		wb_print_state(sc, "Before watchdog attach");

	sc->reg_1 &= ~WB_LDN8_CRF5_KEYB_P20;
	sc->reg_1 |= WB_LDN8_CRF5_KBRST;
	superio_write(dev, sc->ctl_reg, sc->reg_1);

	/*
	 * Clear a previous watchdog timeout event (if still set).
	 * Disable timer reset on mouse interrupts.  Leave reset on keyboard,
	 * since one of my boards is getting stuck in reboot without it.
	 */
	sc->reg_2 &= ~(WB_LDN8_CRF7_MOUSE|WB_LDN8_CRF7_TS);
	superio_write(dev, sc->csr_reg, sc->reg_2);

	/* Read global timeout override tunable, Add per device sysctls. */
	if (TUNABLE_ULONG_FETCH("hw.wbwd.timeout_override", &timeout)) {
		if (timeout > 0)
			sc->timeout_override = timeout;
	}
	sctx = device_get_sysctl_ctx(dev);
	soid = device_get_sysctl_tree(dev);
        SYSCTL_ADD_UINT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO,
	    "timeout_override", CTLFLAG_RW, &sc->timeout_override, 0,
            "Timeout in seconds overriding default watchdog timeout");
        SYSCTL_ADD_INT(sctx, SYSCTL_CHILDREN(soid), OID_AUTO,
	    "debug_verbose", CTLFLAG_RW, &sc->debug_verbose, 0,
            "Enables extra debugging information");
        SYSCTL_ADD_PROC(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "debug",
	    CTLTYPE_STRING|CTLFLAG_RD, sc, 0, sysctl_wb_debug, "A",
            "Selected register information from last change by driver");
        SYSCTL_ADD_PROC(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "debug_current",
	    CTLTYPE_STRING|CTLFLAG_RD|CTLFLAG_SKIP, sc, 0,
	     sysctl_wb_debug_current, "A",
	     "Selected register information (may interfere)");
	SYSCTL_ADD_PROC(sctx, SYSCTL_CHILDREN(soid), OID_AUTO, "force_timeout",
	    CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_SKIP, sc, 0,
	    sysctl_wb_force_test_nmi, "I", "Enable to force watchdog to fire.");

	/* Register watchdog. */
	sc->ev_tag = EVENTHANDLER_REGISTER(watchdog_list, wb_watchdog_fn, sc,
	    0);

	if (bootverbose)
		wb_print_state(sc, "After watchdog attach");

	return (0);
}