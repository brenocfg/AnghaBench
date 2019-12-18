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
typedef  int uint64_t ;
struct hwpstate_softc {int cfnum; struct hwpstate_setting* hwpstate_settings; } ;
struct hwpstate_setting {int freq; int pstate_id; void* lat; void* power; void* volts; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AMD_10H_11H_CUR_DID (int) ; 
 int AMD_10H_11H_CUR_FID (int) ; 
 int AMD_10H_11H_GET_PSTATE_MAX_VAL (int) ; 
 int AMD_17H_CUR_DID (int) ; 
 int AMD_17H_CUR_FID (int) ; 
 void* CPUFREQ_VAL_UNKNOWN ; 
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  HWPSTATE_DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ MSR_AMD_10H_11H_CONFIG ; 
 scalar_t__ MSR_AMD_10H_11H_LIMIT ; 
 int /*<<< orphan*/  cpu_id ; 
 struct hwpstate_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rdmsr (scalar_t__) ; 

__attribute__((used)) static int
hwpstate_get_info_from_msr(device_t dev)
{
	struct hwpstate_softc *sc;
	struct hwpstate_setting *hwpstate_set;
	uint64_t msr;
	int family, i, fid, did;

	family = CPUID_TO_FAMILY(cpu_id);
	sc = device_get_softc(dev);
	/* Get pstate count */
	msr = rdmsr(MSR_AMD_10H_11H_LIMIT);
	sc->cfnum = 1 + AMD_10H_11H_GET_PSTATE_MAX_VAL(msr);
	hwpstate_set = sc->hwpstate_settings;
	for (i = 0; i < sc->cfnum; i++) {
		msr = rdmsr(MSR_AMD_10H_11H_CONFIG + i);
		if ((msr & ((uint64_t)1 << 63)) == 0) {
			HWPSTATE_DEBUG(dev, "msr is not valid.\n");
			return (ENXIO);
		}
		did = AMD_10H_11H_CUR_DID(msr);
		fid = AMD_10H_11H_CUR_FID(msr);

		/* Convert fid/did to frequency. */
		switch (family) {
		case 0x11:
			hwpstate_set[i].freq = (100 * (fid + 0x08)) >> did;
			break;
		case 0x10:
		case 0x12:
		case 0x15:
		case 0x16:
			hwpstate_set[i].freq = (100 * (fid + 0x10)) >> did;
			break;
		case 0x17:
			did = AMD_17H_CUR_DID(msr);
			if (did == 0) {
				HWPSTATE_DEBUG(dev, "unexpected did: 0\n");
				did = 1;
			}
			fid = AMD_17H_CUR_FID(msr);
			hwpstate_set[i].freq = (200 * fid) / did;
			break;
		default:
			HWPSTATE_DEBUG(dev, "get_info_from_msr: AMD family"
			    " 0x%02x CPUs are not supported yet\n", family);
			return (ENXIO);
		}
		hwpstate_set[i].pstate_id = i;
		/* There was volts calculation, but deleted it. */
		hwpstate_set[i].volts = CPUFREQ_VAL_UNKNOWN;
		hwpstate_set[i].power = CPUFREQ_VAL_UNKNOWN;
		hwpstate_set[i].lat = CPUFREQ_VAL_UNKNOWN;
	}
	return (0);
}