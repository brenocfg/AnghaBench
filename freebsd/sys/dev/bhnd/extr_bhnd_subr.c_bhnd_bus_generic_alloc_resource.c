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
typedef  int u_int ;
struct resource {int dummy; } ;
struct bhnd_resource {int direct; struct resource* res; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BHND_BUS_ACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct bhnd_resource*) ; 
 struct resource* BUS_ALLOC_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BUS_RELEASE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int RF_ACTIVE ; 
 int /*<<< orphan*/  free (struct bhnd_resource*,int /*<<< orphan*/ ) ; 
 struct bhnd_resource* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct bhnd_resource *
bhnd_bus_generic_alloc_resource(device_t dev, device_t child, int type,
	int *rid, rman_res_t start, rman_res_t end, rman_res_t count,
	u_int flags)
{
	struct bhnd_resource	*br;
	struct resource		*res;
	int			 error;

	br = NULL;
	res = NULL;

	/* Allocate the real bus resource (without activating it) */
	res = BUS_ALLOC_RESOURCE(dev, child, type, rid, start, end, count,
	    (flags & ~RF_ACTIVE));
	if (res == NULL)
		return (NULL);

	/* Allocate our bhnd resource wrapper. */
	br = malloc(sizeof(struct bhnd_resource), M_BHND, M_NOWAIT);
	if (br == NULL)
		goto failed;
	
	br->direct = false;
	br->res = res;

	/* Attempt activation */
	if (flags & RF_ACTIVE) {
		error = BHND_BUS_ACTIVATE_RESOURCE(dev, child, type, *rid, br);
		if (error)
			goto failed;
	}

	return (br);
	
failed:
	if (res != NULL)
		BUS_RELEASE_RESOURCE(dev, child, type, *rid, res);

	free(br, M_BHND);
	return (NULL);
}