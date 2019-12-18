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
struct g_llvm_vg {int dummy; } ;
struct g_geom {struct g_llvm_vg* softc; } ;
struct g_consumer {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_llvm_destroy (struct g_llvm_vg*,int) ; 
 int /*<<< orphan*/  g_llvm_remove_disk (struct g_llvm_vg*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_llvm_orphan(struct g_consumer *cp)
{
	struct g_llvm_vg *vg;
	struct g_geom *gp;

	g_topology_assert();
	gp = cp->geom;
	vg = gp->softc;
	if (vg == NULL)
		return;

	g_llvm_remove_disk(vg, cp);
	g_llvm_destroy(vg, 1);
}