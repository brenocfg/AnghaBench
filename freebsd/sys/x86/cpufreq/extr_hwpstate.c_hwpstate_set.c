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
struct hwpstate_softc {int cfnum; struct hwpstate_setting* hwpstate_settings; } ;
struct hwpstate_setting {int /*<<< orphan*/  pstate_id; int /*<<< orphan*/  freq; } ;
struct cf_setting {int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ CPUFREQ_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct hwpstate_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hwpstate_goto_pstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hwpstate_set(device_t dev, const struct cf_setting *cf)
{
	struct hwpstate_softc *sc;
	struct hwpstate_setting *set;
	int i;

	if (cf == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);
	set = sc->hwpstate_settings;
	for (i = 0; i < sc->cfnum; i++)
		if (CPUFREQ_CMP(cf->freq, set[i].freq))
			break;
	if (i == sc->cfnum)
		return (EINVAL);

	return (hwpstate_goto_pstate(dev, set[i].pstate_id));
}