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

/* Variables and functions */
 int /*<<< orphan*/  emu_midi_card_intr (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emu_midi_intr(void *p)
{
	(void)emu_midi_card_intr(p, 0);
}