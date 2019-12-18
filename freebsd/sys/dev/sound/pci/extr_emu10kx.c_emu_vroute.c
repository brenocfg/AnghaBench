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
struct emu_voice {scalar_t__ ismaster; struct emu_voice* slave; scalar_t__ stereo; int /*<<< orphan*/ * amounts; int /*<<< orphan*/ * routing; } ;
struct emu_sc_info {int dummy; } ;
struct emu_route {int /*<<< orphan*/ * amounts_right; int /*<<< orphan*/ * routing_right; int /*<<< orphan*/ * amounts_left; int /*<<< orphan*/ * routing_left; } ;

/* Variables and functions */

void
emu_vroute(struct emu_sc_info *sc, struct emu_route *rt,  struct emu_voice *v)
{
	int i;

	for (i = 0; i < 8; i++) {
		v->routing[i] = rt->routing_left[i];
		v->amounts[i] = rt->amounts_left[i];
	}
	if ((v->stereo) && (v->ismaster == 0))
		for (i = 0; i < 8; i++) {
			v->routing[i] = rt->routing_right[i];
			v->amounts[i] = rt->amounts_right[i];
		}

	if ((v->stereo) && (v->slave != NULL))
		emu_vroute(sc, rt, v->slave);
}