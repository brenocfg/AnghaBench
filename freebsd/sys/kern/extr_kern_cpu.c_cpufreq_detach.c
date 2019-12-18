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
struct cpufreq_softc {struct cf_saved_freq* levels_buf; int /*<<< orphan*/  saved_freq; int /*<<< orphan*/  sysctl_ctx; } ;
struct cf_saved_freq {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CF_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_TEMP ; 
 struct cf_saved_freq* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_dc ; 
 int devclass_get_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct cpufreq_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cf_saved_freq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cpufreq_detach(device_t dev)
{
	struct cpufreq_softc *sc;
	struct cf_saved_freq *saved_freq;
	int numdevs;

	CF_DEBUG("shutdown %s\n", device_get_nameunit(dev));
	sc = device_get_softc(dev);
	sysctl_ctx_free(&sc->sysctl_ctx);

	while ((saved_freq = SLIST_FIRST(&sc->saved_freq)) != NULL) {
		SLIST_REMOVE_HEAD(&sc->saved_freq, link);
		free(saved_freq, M_TEMP);
	}

	/* Only clean up these resources when the last device is detaching. */
	numdevs = devclass_get_count(cpufreq_dc);
	if (numdevs == 1) {
		CF_DEBUG("final shutdown for %s\n", device_get_nameunit(dev));
		free(sc->levels_buf, M_DEVBUF);
	}

	return (0);
}