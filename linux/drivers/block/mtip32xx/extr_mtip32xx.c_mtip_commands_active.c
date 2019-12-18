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
struct mtip_port {int /*<<< orphan*/ * s_active; TYPE_1__* dd; } ;
struct TYPE_2__ {unsigned int slot_groups; } ;

/* Variables and functions */
 unsigned int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mtip_commands_active(struct mtip_port *port)
{
	unsigned int active;
	unsigned int n;

	/*
	 * Ignore s_active bit 0 of array element 0.
	 * This bit will always be set
	 */
	active = readl(port->s_active[0]) & 0xFFFFFFFE;
	for (n = 1; n < port->dd->slot_groups; n++)
		active |= readl(port->s_active[n]);

	return active != 0;
}