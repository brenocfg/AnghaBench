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
typedef  size_t uint32_t ;
struct octeon_device {size_t num_consoles; TYPE_1__* console_timer; struct lio_console* console; } ;
struct lio_console {scalar_t__ output_base_addr; scalar_t__ input_base_addr; scalar_t__ buffer_size; scalar_t__ addr; int /*<<< orphan*/  active; } ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

void
lio_remove_consoles(struct octeon_device *oct)
{
	struct lio_console	*console;
	uint32_t		i;

	for (i = 0; i < oct->num_consoles; i++) {
		console = &oct->console[i];

		if (!console->active)
			continue;

		callout_stop(&oct->console_timer[i].timer);
		console->addr = 0;
		console->buffer_size = 0;
		console->input_base_addr = 0;
		console->output_base_addr = 0;
	}

	oct->num_consoles = 0;
}