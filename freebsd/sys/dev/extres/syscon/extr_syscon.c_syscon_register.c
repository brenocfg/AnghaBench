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
struct syscon {scalar_t__ ofw_node; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (scalar_t__) ; 
 int SYSCON_INIT (struct syscon*) ; 
 int /*<<< orphan*/  SYSCON_TOPO_UNLOCK () ; 
 int /*<<< orphan*/  SYSCON_TOPO_XLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct syscon*,int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  syscon_link ; 
 int /*<<< orphan*/  syscon_list ; 

struct syscon *
syscon_register(struct syscon *syscon)
{
	int rv;

#ifdef FDT
	if (syscon->ofw_node <= 0)
		syscon->ofw_node = ofw_bus_get_node(syscon->pdev);
	if (syscon->ofw_node <= 0)
		return (NULL);
#endif

	rv = SYSCON_INIT(syscon);
	if (rv != 0) {
		printf("SYSCON_INIT failed: %d\n", rv);
		return (NULL);
	}

#ifdef FDT
	OF_device_register_xref(OF_xref_from_node(syscon->ofw_node),
	    syscon->pdev);
#endif
	SYSCON_TOPO_XLOCK();
	TAILQ_INSERT_TAIL(&syscon_list, syscon, syscon_link);
	SYSCON_TOPO_UNLOCK();
	return (syscon);
}