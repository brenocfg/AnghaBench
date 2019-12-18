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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BUS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bus_child_location_str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bus_child_pnpinfo_str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devctl_queue_data (char*) ; 
 int /*<<< orphan*/  devctl_queue_length ; 
 char* device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char*,char*,char const*) ; 

__attribute__((used)) static void
devaddq(const char *type, const char *what, device_t dev)
{
	char *data = NULL;
	char *loc = NULL;
	char *pnp = NULL;
	const char *parstr;

	if (!devctl_queue_length)/* Rare race, but lost races safely discard */
		return;
	data = malloc(1024, M_BUS, M_NOWAIT);
	if (data == NULL)
		goto bad;

	/* get the bus specific location of this device */
	loc = malloc(1024, M_BUS, M_NOWAIT);
	if (loc == NULL)
		goto bad;
	*loc = '\0';
	bus_child_location_str(dev, loc, 1024);

	/* Get the bus specific pnp info of this device */
	pnp = malloc(1024, M_BUS, M_NOWAIT);
	if (pnp == NULL)
		goto bad;
	*pnp = '\0';
	bus_child_pnpinfo_str(dev, pnp, 1024);

	/* Get the parent of this device, or / if high enough in the tree. */
	if (device_get_parent(dev) == NULL)
		parstr = ".";	/* Or '/' ? */
	else
		parstr = device_get_nameunit(device_get_parent(dev));
	/* String it all together. */
	snprintf(data, 1024, "%s%s at %s %s on %s\n", type, what, loc, pnp,
	  parstr);
	free(loc, M_BUS);
	free(pnp, M_BUS);
	devctl_queue_data(data);
	return;
bad:
	free(pnp, M_BUS);
	free(loc, M_BUS);
	free(data, M_BUS);
	return;
}