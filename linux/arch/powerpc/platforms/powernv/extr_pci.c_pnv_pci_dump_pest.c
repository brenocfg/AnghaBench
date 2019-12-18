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
typedef  int __be64 ;

/* Variables and functions */
 int PNV_IODA_STOPPED_STATE ; 
 int ULONG_MAX ; 
 int be64_to_cpu (int) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 

__attribute__((used)) static void pnv_pci_dump_pest(__be64 pestA[], __be64 pestB[], int pest_size)
{
	__be64 prevA = ULONG_MAX, prevB = ULONG_MAX;
	bool dup = false;
	int i;

	for (i = 0; i < pest_size; i++) {
		__be64 peA = be64_to_cpu(pestA[i]);
		__be64 peB = be64_to_cpu(pestB[i]);

		if (peA != prevA || peB != prevB) {
			if (dup) {
				pr_info("PE[..%03x] A/B: as above\n", i-1);
				dup = false;
			}
			prevA = peA;
			prevB = peB;
			if (peA & PNV_IODA_STOPPED_STATE ||
			    peB & PNV_IODA_STOPPED_STATE)
				pr_info("PE[%03x] A/B: %016llx %016llx\n",
					i, peA, peB);
		} else if (!dup && (peA & PNV_IODA_STOPPED_STATE ||
				    peB & PNV_IODA_STOPPED_STATE)) {
			dup = true;
		}
	}
}