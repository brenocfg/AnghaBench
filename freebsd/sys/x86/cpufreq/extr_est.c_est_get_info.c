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
typedef  int /*<<< orphan*/  uint64_t ;
struct est_softc {int /*<<< orphan*/  flist_len; int /*<<< orphan*/  freq_list; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MSR_PERF_STATUS ; 
 char* cpu_vendor ; 
 struct est_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int est_acpi_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int est_msr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int est_table_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
est_get_info(device_t dev)
{
	struct est_softc *sc;
	uint64_t msr;
	int error;

	sc = device_get_softc(dev);
	msr = rdmsr(MSR_PERF_STATUS);
	error = est_table_info(dev, msr, &sc->freq_list, &sc->flist_len);
	if (error)
		error = est_acpi_info(dev, &sc->freq_list, &sc->flist_len);
	if (error)
		error = est_msr_info(dev, msr, &sc->freq_list, &sc->flist_len);

	if (error) {
		printf(
	"est: CPU supports Enhanced Speedstep, but is not recognized.\n"
	"est: cpu_vendor %s, msr %0jx\n", cpu_vendor, msr);
		return (ENXIO);
	}

	return (0);
}