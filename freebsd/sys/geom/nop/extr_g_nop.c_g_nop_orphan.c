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
struct g_consumer {int /*<<< orphan*/  geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_nop_destroy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_nop_orphan(struct g_consumer *cp)
{

	g_topology_assert();
	g_nop_destroy(cp->geom, 1);
}