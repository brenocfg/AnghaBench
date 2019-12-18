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
struct g_consumer {TYPE_1__* geom; } ;
struct TYPE_2__ {int /*<<< orphan*/  softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_cache_destroy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_cache_orphan(struct g_consumer *cp)
{

	g_topology_assert();
	g_cache_destroy(cp->geom->softc, 1);
}