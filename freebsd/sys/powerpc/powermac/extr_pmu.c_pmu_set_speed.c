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
typedef  char uint8_t ;
struct pmu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_CPU_SPEED ; 
 struct pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mtdec (int) ; 
 int /*<<< orphan*/  platform_sleep () ; 
 int /*<<< orphan*/  pmu ; 
 int /*<<< orphan*/  pmu_send (struct pmu_softc*,int /*<<< orphan*/ ,int,char*,int,char*) ; 
 int /*<<< orphan*/  pmu_write_reg (struct pmu_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spinlock_enter () ; 
 int /*<<< orphan*/  spinlock_exit () ; 
 int /*<<< orphan*/  unin_chip_sleep (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unin_chip_wake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vIER ; 

int
pmu_set_speed(int low_speed)
{
	struct pmu_softc *sc;
	uint8_t sleepcmd[] = {'W', 'O', 'O', 'F', 0};
	uint8_t resp[16];

	sc = device_get_softc(pmu);
	pmu_write_reg(sc, vIER, 0x10);
	spinlock_enter();
	mtdec(0x7fffffff);
	mb();
	mtdec(0x7fffffff);

	sleepcmd[4] = low_speed;
	pmu_send(sc, PMU_CPU_SPEED, 5, sleepcmd, 16, resp);
	unin_chip_sleep(NULL, 1);
	platform_sleep();
	unin_chip_wake(NULL);

	mtdec(1);	/* Force a decrementer exception */
	spinlock_exit();
	pmu_write_reg(sc, vIER, 0x90);

	return (0);
}