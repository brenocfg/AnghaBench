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
typedef  scalar_t__ uint64_t ;
struct tegra124_cpufreq_softc {int speedo_value; TYPE_1__* cpu_def; } ;
struct speedo_entry {scalar_t__ freq; int c2; int c1; int c0; } ;
struct TYPE_2__ {int speedo_nitems; int speedo_scale; int step_uvolt; int min_uvolt; int /*<<< orphan*/  max_uvolt; struct speedo_entry* speedo_tbl; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int ROUND_DOWN (int /*<<< orphan*/ ,int) ; 
 int ROUND_UP (int,int) ; 

__attribute__((used)) static int
freq_to_voltage(struct tegra124_cpufreq_softc *sc, uint64_t freq)
{
	int uv, scale, min_uvolt, max_uvolt, step_uvolt;
	struct speedo_entry *ent;
	int i;

	/* Get speedo entry with higher frequency */
	ent = NULL;
	for (i = 0; i < sc->cpu_def->speedo_nitems; i++) {
		if (sc->cpu_def->speedo_tbl[i].freq >= freq) {
			ent = &sc->cpu_def->speedo_tbl[i];
			break;
		}
	}
	if (ent == NULL)
		ent = &sc->cpu_def->speedo_tbl[sc->cpu_def->speedo_nitems - 1];
	scale = sc->cpu_def->speedo_scale;


	/* uV = (c2 * speedo / scale + c1) * speedo / scale + c0) */
	uv = DIV_ROUND_CLOSEST(ent->c2 * sc->speedo_value, scale);
	uv = DIV_ROUND_CLOSEST((uv + ent->c1) * sc->speedo_value, scale) +
	    ent->c0;
	step_uvolt = sc->cpu_def->step_uvolt;
	/* Round up it to next regulator step */
	uv = ROUND_UP(uv, step_uvolt);

	/* Clamp result */
	min_uvolt = ROUND_UP(sc->cpu_def->min_uvolt, step_uvolt);
	max_uvolt = ROUND_DOWN(sc->cpu_def->max_uvolt, step_uvolt);
	if (uv < min_uvolt)
		uv =  min_uvolt;
	if (uv > max_uvolt)
		uv =  max_uvolt;
	return (uv);

}