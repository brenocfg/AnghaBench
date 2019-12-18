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
typedef  size_t uint32_t ;
struct oppt {int /*<<< orphan*/  mv; int /*<<< orphan*/  mhz; } ;
struct imx6_anatop_softc {int refosc_mhz; int /*<<< orphan*/  cpu_maxmv; int /*<<< orphan*/  cpu_maxmhz; int /*<<< orphan*/  cpu_minmv; int /*<<< orphan*/  cpu_minmhz; int /*<<< orphan*/  cpu_maxmhz_hw; int /*<<< orphan*/  cpu_overclock_enable; int /*<<< orphan*/  cpu_curmhz; } ;

/* Variables and functions */
 int CTLFLAG_NOFETCH ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  FSL_OCOTP_CFG3 ; 
 size_t FSL_OCOTP_CFG3_SPEED_MASK ; 
 size_t FSL_OCOTP_CFG3_SPEED_SHIFT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct imx6_anatop_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _hw_imx ; 
 struct oppt* cpufreq_nearest_oppt (struct imx6_anatop_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_set_clock (struct imx6_anatop_softc*,struct oppt*) ; 
 int /*<<< orphan*/  cpufreq_sysctl_maxmhz ; 
 int /*<<< orphan*/  cpufreq_sysctl_minmhz ; 
 size_t fsl_ocotp_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * imx6_ocotp_mhz_tab ; 

__attribute__((used)) static void
cpufreq_initialize(struct imx6_anatop_softc *sc)
{
	uint32_t cfg3speed;
	struct oppt * op;

	SYSCTL_ADD_INT(NULL, SYSCTL_STATIC_CHILDREN(_hw_imx),
	    OID_AUTO, "cpu_mhz", CTLFLAG_RD, &sc->cpu_curmhz, 0, 
	    "CPU frequency");

	SYSCTL_ADD_PROC(NULL, SYSCTL_STATIC_CHILDREN(_hw_imx), 
	    OID_AUTO, "cpu_minmhz", CTLTYPE_INT | CTLFLAG_RWTUN | CTLFLAG_NOFETCH,
	    sc, 0, cpufreq_sysctl_minmhz, "IU", "Minimum CPU frequency");

	SYSCTL_ADD_PROC(NULL, SYSCTL_STATIC_CHILDREN(_hw_imx),
	    OID_AUTO, "cpu_maxmhz", CTLTYPE_INT | CTLFLAG_RWTUN | CTLFLAG_NOFETCH,
	    sc, 0, cpufreq_sysctl_maxmhz, "IU", "Maximum CPU frequency");

	SYSCTL_ADD_INT(NULL, SYSCTL_STATIC_CHILDREN(_hw_imx),
	    OID_AUTO, "cpu_maxmhz_hw", CTLFLAG_RD, &sc->cpu_maxmhz_hw, 0, 
	    "Maximum CPU frequency allowed by hardware");

	SYSCTL_ADD_INT(NULL, SYSCTL_STATIC_CHILDREN(_hw_imx),
	    OID_AUTO, "cpu_overclock_enable", CTLFLAG_RWTUN, 
	    &sc->cpu_overclock_enable, 0, 
	    "Allow setting CPU frequency higher than cpu_maxmhz_hw");

	/*
	 * XXX 24mhz shouldn't be hard-coded, should get this from imx6_ccm
	 * (even though in the real world it will always be 24mhz).  Oh wait a
	 * sec, I never wrote imx6_ccm.
	 */
	sc->refosc_mhz = 24;

	/*
	 * Get the maximum speed this cpu can be set to.  The values in the
	 * OCOTP CFG3 register are not documented in the reference manual.
	 * The following info was in an archived email found via web search:
	 *   - 2b'11: 1200000000Hz;
	 *   - 2b'10: 996000000Hz;
	 *   - 2b'01: 852000000Hz; -- i.MX6Q Only, exclusive with 996MHz.
	 *   - 2b'00: 792000000Hz;
	 * The default hardware max speed can be overridden by a tunable.
	 */
	cfg3speed = (fsl_ocotp_read_4(FSL_OCOTP_CFG3) & 
	    FSL_OCOTP_CFG3_SPEED_MASK) >> FSL_OCOTP_CFG3_SPEED_SHIFT;
	sc->cpu_maxmhz_hw = imx6_ocotp_mhz_tab[cfg3speed];
	sc->cpu_maxmhz = sc->cpu_maxmhz_hw;

	TUNABLE_INT_FETCH("hw.imx6.cpu_minmhz", &sc->cpu_minmhz);
	op = cpufreq_nearest_oppt(sc, sc->cpu_minmhz);
	sc->cpu_minmhz = op->mhz;
	sc->cpu_minmv = op->mv;

	TUNABLE_INT_FETCH("hw.imx6.cpu_maxmhz", &sc->cpu_maxmhz);
	op = cpufreq_nearest_oppt(sc, sc->cpu_maxmhz);
	sc->cpu_maxmhz = op->mhz;
	sc->cpu_maxmv = op->mv;

	/*
	 * Set the CPU to maximum speed.
	 *
	 * We won't have thermal throttling until interrupts are enabled, but we
	 * want to run at full speed through all the device init stuff.  This
	 * basically assumes that a single core can't overheat before interrupts
	 * are enabled; empirical testing shows that to be a safe assumption.
	 */
	cpufreq_set_clock(sc, op);
}