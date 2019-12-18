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
struct smu_softc {int sc_cpu_diode_scale; int sc_cpu_volt_scale; int sc_cpu_volt_offset; int sc_cpu_curr_scale; int sc_cpu_curr_offset; int sc_slots_pow_scale; int sc_slots_pow_offset; int /*<<< orphan*/  sc_cpu_diode_offset; } ;
struct smu_sensor {int reg; int type; int /*<<< orphan*/  dev; } ;
struct smu_cmd {int len; int* data; int /*<<< orphan*/  cmd; } ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMU_ADC ; 
#define  SMU_CURRENT_SENSOR 131 
#define  SMU_POWER_SENSOR 130 
#define  SMU_TEMP_SENSOR 129 
#define  SMU_VOLTAGE_SENSOR 128 
 struct smu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int smu_run_cmd (int /*<<< orphan*/ ,struct smu_cmd*,int) ; 

__attribute__((used)) static int
smu_sensor_read(struct smu_sensor *sens)
{
	device_t smu = sens->dev;
	struct smu_cmd cmd;
	struct smu_softc *sc;
	int64_t value;
	int error;

	cmd.cmd = SMU_ADC;
	cmd.len = 1;
	cmd.data[0] = sens->reg;
	error = 0;

	error = smu_run_cmd(smu, &cmd, 1);
	if (error != 0)
		return (-1);
	
	sc = device_get_softc(smu);
	value = (cmd.data[0] << 8) | cmd.data[1];

	switch (sens->type) {
	case SMU_TEMP_SENSOR:
		value *= sc->sc_cpu_diode_scale;
		value >>= 3;
		value += ((int64_t)sc->sc_cpu_diode_offset) << 9;
		value <<= 1;

		/* Convert from 16.16 fixed point degC into integer 0.1 K. */
		value = 10*(value >> 16) + ((10*(value & 0xffff)) >> 16) + 2731;
		break;
	case SMU_VOLTAGE_SENSOR:
		value *= sc->sc_cpu_volt_scale;
		value += sc->sc_cpu_volt_offset;
		value <<= 4;

		/* Convert from 16.16 fixed point V into mV. */
		value *= 15625;
		value /= 1024;
		value /= 1000;
		break;
	case SMU_CURRENT_SENSOR:
		value *= sc->sc_cpu_curr_scale;
		value += sc->sc_cpu_curr_offset;
		value <<= 4;

		/* Convert from 16.16 fixed point A into mA. */
		value *= 15625;
		value /= 1024;
		value /= 1000;
		break;
	case SMU_POWER_SENSOR:
		value *= sc->sc_slots_pow_scale;
		value += sc->sc_slots_pow_offset;
		value <<= 4;

		/* Convert from 16.16 fixed point W into mW. */
		value *= 15625;
		value /= 1024;
		value /= 1000;
		break;
	}

	return (value);
}