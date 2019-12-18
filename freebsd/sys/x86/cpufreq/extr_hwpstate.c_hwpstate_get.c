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
typedef  size_t uint64_t ;
struct hwpstate_softc {size_t cfnum; struct hwpstate_setting* hwpstate_settings; } ;
struct hwpstate_setting {int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MSR_AMD_10H_11H_STATUS ; 
 struct hwpstate_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hwpstate_get(device_t dev, struct cf_setting *cf)
{
	struct hwpstate_softc *sc;
	struct hwpstate_setting set;
	uint64_t msr;

	sc = device_get_softc(dev);
	if (cf == NULL)
		return (EINVAL);
	msr = rdmsr(MSR_AMD_10H_11H_STATUS);
	if (msr >= sc->cfnum)
		return (EINVAL);
	set = sc->hwpstate_settings[msr];

	cf->freq = set.freq;
	cf->volts = set.volts;
	cf->power = set.power;
	cf->lat = set.lat;
	cf->dev = dev;
	return (0);
}