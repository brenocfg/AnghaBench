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
struct smu_softc {int old_style_fans; } ;
struct smu_fan {int reg; int /*<<< orphan*/  dev; } ;
struct smu_cmd {int len; int* data; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  SMU_FAN ; 
 struct smu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int smu_run_cmd (int /*<<< orphan*/ ,struct smu_cmd*,int) ; 

__attribute__((used)) static int
smu_fan_check_old_style(struct smu_fan *fan)
{
	device_t smu = fan->dev;
	struct smu_softc *sc = device_get_softc(smu);
	struct smu_cmd cmd;
	int error;

	if (sc->old_style_fans != -1)
		return (sc->old_style_fans);

	/*
	 * Apple has two fan control mechanisms. We can't distinguish
	 * them except by seeing if the new one fails. If the new one
	 * fails, use the old one.
	 */
	
	cmd.cmd = SMU_FAN;
	cmd.len = 2;
	cmd.data[0] = 0x31;
	cmd.data[1] = fan->reg;

	do {
		error = smu_run_cmd(smu, &cmd, 1);
	} while (error == EWOULDBLOCK);

	sc->old_style_fans = (error != 0);

	return (sc->old_style_fans);
}