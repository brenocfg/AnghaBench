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
typedef  int /*<<< orphan*/  xref ;
struct endpoint {int reg; int slave; scalar_t__ dev_node; int /*<<< orphan*/  their_node; scalar_t__ my_node; } ;
struct coresight_platform_data {int /*<<< orphan*/  mtx_lock; int /*<<< orphan*/  endpoints; int /*<<< orphan*/  out_ports; int /*<<< orphan*/  in_ports; } ;
typedef  int /*<<< orphan*/  port_reg ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_CORESIGHT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 int OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_getproplen (scalar_t__,char*) ; 
 int /*<<< orphan*/  OF_node_from_xref (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct endpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct endpoint* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
coresight_get_ports(phandle_t dev_node,
    struct coresight_platform_data *pdata)
{
	phandle_t node, child;
	pcell_t port_reg;
	phandle_t xref;
	char *name;
	int ret;
	phandle_t endpoint_child;
	struct endpoint *endp;

	child = ofw_bus_find_child(dev_node, "ports");
	if (child)
		node = child;
	else
		node = dev_node;

	for (child = OF_child(node); child != 0; child = OF_peer(child)) {
		ret = OF_getprop_alloc(child, "name", (void **)&name);
		if (ret == -1)
			continue;

		if (strcasecmp(name, "port") ||
		    strncasecmp(name, "port@", 6)) {

			port_reg = -1;
			OF_getencprop(child, "reg", (void *)&port_reg, sizeof(port_reg));

			endpoint_child = ofw_bus_find_child(child, "endpoint");
			if (endpoint_child) {
				if (OF_getencprop(endpoint_child, "remote-endpoint", &xref,
				    sizeof(xref)) == -1) {
					printf("failed\n");
					continue;
				}
				endp = malloc(sizeof(struct endpoint), M_CORESIGHT,
				    M_WAITOK | M_ZERO);
				endp->my_node = endpoint_child;
				endp->their_node = OF_node_from_xref(xref);
				endp->dev_node = dev_node;
				endp->reg = port_reg;
				if (OF_getproplen(endpoint_child, "slave-mode") >= 0) {
					pdata->in_ports++;
					endp->slave = 1;
				} else {
					pdata->out_ports++;
				}

				mtx_lock(&pdata->mtx_lock);
				TAILQ_INSERT_TAIL(&pdata->endpoints, endp, link);
				mtx_unlock(&pdata->mtx_lock);
			}
		}
	}

	return (0);
}