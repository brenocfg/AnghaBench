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
typedef  int uint32_t ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  freq; } ;
struct acpi_throttle_softc {int cpu_thr_state; int /*<<< orphan*/  cpu_p_cnt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_VAL_UNKNOWN ; 
 int CPU_MAX_SPEED ; 
 int /*<<< orphan*/  CPU_SPEED_PERCENT (int) ; 
 int EINVAL ; 
 int THR_GET_REG (int /*<<< orphan*/ ) ; 
 int cpu_duty_offset ; 
 struct acpi_throttle_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cf_setting*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
acpi_thr_get(device_t dev, struct cf_setting *set)
{
	struct acpi_throttle_softc *sc;
	uint32_t p_cnt, clk_val;

	if (set == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	/* Get the current throttling setting from P_CNT. */
	p_cnt = THR_GET_REG(sc->cpu_p_cnt);
	clk_val = (p_cnt >> cpu_duty_offset) & (CPU_MAX_SPEED - 1);
	sc->cpu_thr_state = clk_val;

	memset(set, CPUFREQ_VAL_UNKNOWN, sizeof(*set));
	set->freq = CPU_SPEED_PERCENT(clk_val);
	set->dev = dev;

	return (0);
}