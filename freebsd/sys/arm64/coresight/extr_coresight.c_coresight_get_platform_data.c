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
struct coresight_platform_data {int in_ports; int out_ports; int /*<<< orphan*/  endpoints; int /*<<< orphan*/  mtx_lock; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CORESIGHT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  coresight_get_cpu (int /*<<< orphan*/ ,struct coresight_platform_data*) ; 
 int /*<<< orphan*/  coresight_get_ports (int /*<<< orphan*/ ,struct coresight_platform_data*) ; 
 struct coresight_platform_data* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

struct coresight_platform_data *
coresight_get_platform_data(device_t dev)
{
	struct coresight_platform_data *pdata;
	phandle_t node;

	node = ofw_bus_get_node(dev);

	pdata = malloc(sizeof(struct coresight_platform_data),
	    M_CORESIGHT, M_WAITOK | M_ZERO);
	mtx_init(&pdata->mtx_lock, "Coresight Platform Data", NULL, MTX_DEF);
	TAILQ_INIT(&pdata->endpoints);

	coresight_get_cpu(node, pdata);
	coresight_get_ports(node, pdata);

	if (bootverbose)
		printf("Total ports: in %d out %d\n",
		    pdata->in_ports, pdata->out_ports);

	return (pdata);
}