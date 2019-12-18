#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  clidr; } ;

/* Variables and functions */
 scalar_t__ CACHE_DCACHE ; 
 scalar_t__ CACHE_ICACHE ; 
 scalar_t__ CACHE_SEP_CACHE ; 
 scalar_t__ CACHE_UNI_CACHE ; 
 scalar_t__ CPUV7_CT_CTYPE_RA ; 
 scalar_t__ CPUV7_CT_CTYPE_WA ; 
 scalar_t__ CPUV7_CT_CTYPE_WB ; 
 scalar_t__ CPUV7_CT_CTYPE_WT ; 
 int CPUV7_CT_xSIZE_ASSOC (scalar_t__) ; 
 int CPUV7_CT_xSIZE_LEN (scalar_t__) ; 
 int CPUV7_CT_xSIZE_SET (scalar_t__) ; 
 scalar_t__ CPU_CLIDR_CTYPE (int /*<<< orphan*/ ,int) ; 
 int CPU_CLIDR_LOC (int /*<<< orphan*/ ) ; 
 int CPU_CLIDR_LOUIS (int /*<<< orphan*/ ) ; 
 int CPU_CLIDR_LOUU (int /*<<< orphan*/ ) ; 
 scalar_t__ cp15_ccsidr_get () ; 
 int /*<<< orphan*/  cp15_csselr_set (int) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_v7_cache(void )
{
	uint32_t type, val, size, sets, ways, linesize;
	int i;

	printf("LoUU:%d LoC:%d LoUIS:%d \n",
	    CPU_CLIDR_LOUU(cpuinfo.clidr) + 1,
	    CPU_CLIDR_LOC(cpuinfo.clidr) + 1,
	    CPU_CLIDR_LOUIS(cpuinfo.clidr) + 1);

	for (i = 0; i < 7; i++) {
		type = CPU_CLIDR_CTYPE(cpuinfo.clidr, i);
		if (type == 0)
			break;
		printf("Cache level %d:\n", i + 1);
		if (type == CACHE_DCACHE || type == CACHE_UNI_CACHE ||
		    type == CACHE_SEP_CACHE) {
			cp15_csselr_set(i << 1);
			val = cp15_ccsidr_get();
			ways = CPUV7_CT_xSIZE_ASSOC(val) + 1;
			sets = CPUV7_CT_xSIZE_SET(val) + 1;
			linesize = 1 << (CPUV7_CT_xSIZE_LEN(val) + 4);
			size = (ways * sets * linesize) / 1024;

			if (type == CACHE_UNI_CACHE)
				printf(" %dKB/%dB %d-way unified cache",
				    size, linesize,ways);
			else
				printf(" %dKB/%dB %d-way data cache",
				    size, linesize, ways);
			if (val & CPUV7_CT_CTYPE_WT)
				printf(" WT");
			if (val & CPUV7_CT_CTYPE_WB)
				printf(" WB");
				if (val & CPUV7_CT_CTYPE_RA)
				printf(" Read-Alloc");
			if (val & CPUV7_CT_CTYPE_WA)
				printf(" Write-Alloc");
			printf("\n");
		}

		if (type == CACHE_ICACHE || type == CACHE_SEP_CACHE) {
			cp15_csselr_set(i << 1 | 1);
			val = cp15_ccsidr_get();
			ways = CPUV7_CT_xSIZE_ASSOC(val) + 1;
			sets = CPUV7_CT_xSIZE_SET(val) + 1;
			linesize = 1 << (CPUV7_CT_xSIZE_LEN(val) + 4);
			size = (ways * sets * linesize) / 1024;
				printf(" %dKB/%dB %d-way instruction cache",
			    size, linesize, ways);
			if (val & CPUV7_CT_CTYPE_WT)
				printf(" WT");
			if (val & CPUV7_CT_CTYPE_WB)
				printf(" WB");
			if (val & CPUV7_CT_CTYPE_RA)
				printf(" Read-Alloc");
			if (val & CPUV7_CT_CTYPE_WA)
				printf(" Write-Alloc");
			printf("\n");
		}
	}
	cp15_csselr_set(0);
}