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
typedef  int uint32_t ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct am335x_ehrpwm_softc {int sc_pwm_period; int sc_pwm_dutyA; int sc_pwm_dutyB; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/  sc_mem_rid; int /*<<< orphan*/ * sc_busdev; void* sc_chanB_oid; void* sc_chanA_oid; void* sc_period_oid; void* sc_freq_oid; void* sc_clkdiv_oid; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AQCTL_CAU_CLEAR ; 
 int AQCTL_CBU_CLEAR ; 
 int AQCTL_ZRO_SET ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int DEFAULT_PWM_PERIOD ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPWM_AQCTLA ; 
 int /*<<< orphan*/  EPWM_AQCTLB ; 
 int /*<<< orphan*/  EPWM_CMPA ; 
 int /*<<< orphan*/  EPWM_CMPB ; 
 int EPWM_READ2 (struct am335x_ehrpwm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPWM_TBCTL ; 
 int /*<<< orphan*/  EPWM_TBPRD ; 
 int /*<<< orphan*/  EPWM_TZCTL ; 
 int /*<<< orphan*/  EPWM_TZFLG ; 
 int /*<<< orphan*/  EPWM_WRITE2 (struct am335x_ehrpwm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  PWM_LOCK_DESTROY (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  PWM_LOCK_INIT (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 void* SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct am335x_ehrpwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int TBCTL_CLKDIV_MASK ; 
 int TBCTL_CTRMODE_MASK ; 
 int TBCTL_CTRMODE_UP ; 
 int TBCTL_FREERUN ; 
 int TBCTL_HSPCLKDIV_MASK ; 
 int /*<<< orphan*/  am335x_ehrpwm_freq (struct am335x_ehrpwm_softc*) ; 
 int /*<<< orphan*/  am335x_ehrpwm_sysctl_clkdiv ; 
 int /*<<< orphan*/  am335x_ehrpwm_sysctl_duty ; 
 int /*<<< orphan*/  am335x_ehrpwm_sysctl_freq ; 
 int /*<<< orphan*/  am335x_ehrpwm_sysctl_period ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct am335x_ehrpwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
am335x_ehrpwm_attach(device_t dev)
{
	struct am335x_ehrpwm_softc *sc;
	uint32_t reg;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *tree;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	PWM_LOCK_INIT(sc);

	sc->sc_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->sc_mem_rid, RF_ACTIVE);
	if (sc->sc_mem_res == NULL) {
		device_printf(dev, "cannot allocate memory resources\n");
		goto fail;
	}

	/* Init sysctl interface */
	ctx = device_get_sysctl_ctx(sc->sc_dev);
	tree = device_get_sysctl_tree(sc->sc_dev);

	sc->sc_clkdiv_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "clkdiv", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    am335x_ehrpwm_sysctl_clkdiv, "I", "PWM clock prescaler");

	sc->sc_freq_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "freq", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    am335x_ehrpwm_sysctl_freq, "I", "PWM frequency");

	sc->sc_period_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "period", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    am335x_ehrpwm_sysctl_period, "I", "PWM period");

	sc->sc_chanA_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "dutyA", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    am335x_ehrpwm_sysctl_duty, "I", "Channel A duty cycles");

	sc->sc_chanB_oid = SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
	    "dutyB", CTLTYPE_INT | CTLFLAG_RW, sc, 0,
	    am335x_ehrpwm_sysctl_duty, "I", "Channel B duty cycles");

	/* CONFIGURE EPWM1 */
	reg = EPWM_READ2(sc, EPWM_TBCTL);
	reg &= ~(TBCTL_CLKDIV_MASK | TBCTL_HSPCLKDIV_MASK);
	EPWM_WRITE2(sc, EPWM_TBCTL, reg);

	sc->sc_pwm_period = DEFAULT_PWM_PERIOD;
	sc->sc_pwm_dutyA = 0;
	sc->sc_pwm_dutyB = 0;
	am335x_ehrpwm_freq(sc);

	EPWM_WRITE2(sc, EPWM_TBPRD, sc->sc_pwm_period - 1);
	EPWM_WRITE2(sc, EPWM_CMPA, sc->sc_pwm_dutyA);
	EPWM_WRITE2(sc, EPWM_CMPB, sc->sc_pwm_dutyB);

	EPWM_WRITE2(sc, EPWM_AQCTLA, (AQCTL_ZRO_SET | AQCTL_CAU_CLEAR));
	EPWM_WRITE2(sc, EPWM_AQCTLB, (AQCTL_ZRO_SET | AQCTL_CBU_CLEAR));

	/* START EPWM */
	reg &= ~TBCTL_CTRMODE_MASK;
	reg |= TBCTL_CTRMODE_UP | TBCTL_FREERUN;
	EPWM_WRITE2(sc, EPWM_TBCTL, reg);

	EPWM_WRITE2(sc, EPWM_TZCTL, 0xf);
	reg = EPWM_READ2(sc, EPWM_TZFLG);

	if ((sc->sc_busdev = device_add_child(dev, "pwmbus", -1)) == NULL) {
		device_printf(dev, "Cannot add child pwmbus\n");
		// This driver can still do things even without the bus child.
	}

	bus_generic_probe(dev);
	return (bus_generic_attach(dev));
fail:
	PWM_LOCK_DESTROY(sc);
	if (sc->sc_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->sc_mem_rid, sc->sc_mem_res);

	return(ENXIO);
}