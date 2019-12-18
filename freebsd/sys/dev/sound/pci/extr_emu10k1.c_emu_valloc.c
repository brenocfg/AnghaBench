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
struct sc_info {struct emu_voice* voice; } ;
struct emu_voice {int busy; } ;

/* Variables and functions */

__attribute__((used)) static struct emu_voice *
emu_valloc(struct sc_info *sc)
{
	struct emu_voice *v;
	int i;

	v = NULL;
	for (i = 0; i < 64 && sc->voice[i].busy; i++);
	if (i < 64) {
		v = &sc->voice[i];
		v->busy = 1;
	}
	return v;
}