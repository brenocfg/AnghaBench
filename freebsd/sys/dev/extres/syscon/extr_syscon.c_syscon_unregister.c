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
struct syscon {int /*<<< orphan*/  ofw_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCON_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  SYSCON_TOPO_XLOCK () ; 
 int SYSCON_UNINIT (struct syscon*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct syscon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_link ; 
 int /*<<< orphan*/  syscon_list ; 

int
syscon_unregister(struct syscon *syscon)
{

	SYSCON_TOPO_XLOCK();
	TAILQ_REMOVE(&syscon_list, syscon, syscon_link);
	SYSCON_TOPO_UNLOCK();
#ifdef FDT
	OF_device_register_xref(OF_xref_from_node(syscon->ofw_node), NULL);
#endif
	return (SYSCON_UNINIT(syscon));
}