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
struct clkdom {int /*<<< orphan*/  ofw_mapper; int /*<<< orphan*/  clknode_list; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  M_CLOCK ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct clkdom*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clkdom_sysctl ; 
 int /*<<< orphan*/  clknode_default_ofw_map ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 struct clkdom* malloc (int,int /*<<< orphan*/ ,int) ; 

struct clkdom *
clkdom_create(device_t dev)
{
	struct clkdom *clkdom;

	clkdom = malloc(sizeof(struct clkdom), M_CLOCK, M_WAITOK | M_ZERO);
	clkdom->dev = dev;
	TAILQ_INIT(&clkdom->clknode_list);
#ifdef FDT
	clkdom->ofw_mapper = clknode_default_ofw_map;
#endif

	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	  SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
	  OID_AUTO, "clocks",
	  CTLTYPE_STRING | CTLFLAG_RD,
		    clkdom, 0, clkdom_sysctl,
		    "A",
		    "Clock list for the domain");

	return (clkdom);
}