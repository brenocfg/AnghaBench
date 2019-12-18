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
struct cf_setting {int freq; } ;
struct acpi_throttle_softc {int cpu_thr_state; int /*<<< orphan*/  cpu_p_cnt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CPU_MAX_SPEED ; 
 int CPU_P_CNT_THT_EN ; 
 int EINVAL ; 
 int THR_GET_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THR_SET_REG (int /*<<< orphan*/ ,int) ; 
 int cpu_duty_offset ; 
 struct acpi_throttle_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_thr_set(device_t dev, const struct cf_setting *set)
{
	struct acpi_throttle_softc *sc;
	uint32_t clk_val, p_cnt, speed;

	if (set == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	/*
	 * Validate requested state converts to a duty cycle that is an
	 * integer from [1 .. CPU_MAX_SPEED].
	 */
	speed = set->freq * CPU_MAX_SPEED / 10000;
	if (speed * 10000 != set->freq * CPU_MAX_SPEED ||
	    speed < 1 || speed > CPU_MAX_SPEED)
		return (EINVAL);

	/* If we're at this setting, don't bother applying it again. */
	if (speed == sc->cpu_thr_state)
		return (0);

	/* Get the current P_CNT value and disable throttling */
	p_cnt = THR_GET_REG(sc->cpu_p_cnt);
	p_cnt &= ~CPU_P_CNT_THT_EN;
	THR_SET_REG(sc->cpu_p_cnt, p_cnt);

	/* If we're at maximum speed, that's all */
	if (speed < CPU_MAX_SPEED) {
		/* Mask the old CLK_VAL off and OR in the new value */
		clk_val = (CPU_MAX_SPEED - 1) << cpu_duty_offset;
		p_cnt &= ~clk_val;
		p_cnt |= (speed << cpu_duty_offset);

		/* Write the new P_CNT value and then enable throttling */
		THR_SET_REG(sc->cpu_p_cnt, p_cnt);
		p_cnt |= CPU_P_CNT_THT_EN;
		THR_SET_REG(sc->cpu_p_cnt, p_cnt);
	}
	sc->cpu_thr_state = speed;

	return (0);
}