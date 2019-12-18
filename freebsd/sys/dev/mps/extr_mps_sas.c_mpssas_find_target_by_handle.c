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
typedef  scalar_t__ uint16_t ;
struct mpssas_target {scalar_t__ handle; } ;
struct mpssas_softc {int maxtargets; struct mpssas_target* targets; } ;

/* Variables and functions */

struct mpssas_target *
mpssas_find_target_by_handle(struct mpssas_softc *sassc, int start, uint16_t handle)
{
	struct mpssas_target *target;
	int i;

	for (i = start; i < sassc->maxtargets; i++) {
		target = &sassc->targets[i];
		if (target->handle == handle)
			return (target);
	}

	return (NULL);
}