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
struct cpufreq_softc {int /*<<< orphan*/  max_mhz; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_settings_sysctl ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct cpufreq_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ *) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ *) ; 

int
cpufreq_register(device_t dev)
{
	struct cpufreq_softc *sc;
	device_t cf_dev, cpu_dev;

	/* Add a sysctl to get each driver's settings separately. */
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	    OID_AUTO, "freq_settings", CTLTYPE_STRING | CTLFLAG_RD, dev, 0,
	    cpufreq_settings_sysctl, "A", "CPU frequency driver settings");

	/*
	 * Add only one cpufreq device to each CPU.  Currently, all CPUs
	 * must offer the same levels and be switched at the same time.
	 */
	cpu_dev = device_get_parent(dev);
	if ((cf_dev = device_find_child(cpu_dev, "cpufreq", -1))) {
		sc = device_get_softc(cf_dev);
		sc->max_mhz = CPUFREQ_VAL_UNKNOWN;
		return (0);
	}

	/* Add the child device and possibly sysctls. */
	cf_dev = BUS_ADD_CHILD(cpu_dev, 0, "cpufreq", -1);
	if (cf_dev == NULL)
		return (ENOMEM);
	device_quiet(cf_dev);

	return (device_probe_and_attach(cf_dev));
}