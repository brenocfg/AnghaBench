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
struct vxlan_softc {int /*<<< orphan*/ * vxl_sysctl_node; int /*<<< orphan*/  vxl_sysctl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vxlan_sysctl_destroy(struct vxlan_softc *sc)
{

	sysctl_ctx_free(&sc->vxl_sysctl_ctx);
	sc->vxl_sysctl_node = NULL;
}