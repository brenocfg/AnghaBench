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
typedef  int uint8_t ;
struct pcpu {int pc_cpuid; scalar_t__ pc_awake; int /*<<< orphan*/  pc_hwref; } ;
typedef  int /*<<< orphan*/  reset ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int EBUSY ; 
 int ENXIO ; 
 int OF_getprop (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct pcpu* ap_pcpu ; 
 int* pmap_mapdev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static int
powermac_smp_start_cpu(platform_t plat, struct pcpu *pc)
{
#ifdef SMP
	phandle_t cpu;
	volatile uint8_t *rstvec;
	static volatile uint8_t *rstvec_virtbase = NULL;
	int res, reset, timeout;

	cpu = pc->pc_hwref;
	res = OF_getprop(cpu, "soft-reset", &reset, sizeof(reset));
	if (res < 0) {
		reset = 0x58;

		switch (pc->pc_cpuid) {
		case 0:
			reset += 0x03;
			break;
		case 1:
			reset += 0x04;
			break;
		case 2:
			reset += 0x0f;
			break;
		case 3:
			reset += 0x10;
			break;
		default:
			return (ENXIO);
		}
	}

	ap_pcpu = pc;

	if (rstvec_virtbase == NULL)
		rstvec_virtbase = pmap_mapdev(0x80000000, PAGE_SIZE);

	rstvec = rstvec_virtbase + reset;

	*rstvec = 4;
	powerpc_sync();
	(void)(*rstvec);
	powerpc_sync();
	DELAY(1);
	*rstvec = 0;
	powerpc_sync();
	(void)(*rstvec);
	powerpc_sync();

	timeout = 10000;
	while (!pc->pc_awake && timeout--)
		DELAY(100);

	return ((pc->pc_awake) ? 0 : EBUSY);
#else
	/* No SMP support */
	return (ENXIO);
#endif
}