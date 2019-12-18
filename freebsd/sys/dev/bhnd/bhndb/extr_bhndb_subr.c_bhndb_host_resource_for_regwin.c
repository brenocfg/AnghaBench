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
typedef  size_t u_int ;
struct resource_spec {int type; scalar_t__ rid; } ;
struct resource {int dummy; } ;
struct TYPE_2__ {int type; scalar_t__ rid; } ;
struct bhndb_regwin {TYPE_1__ res; } ;
struct bhndb_host_resources {int /*<<< orphan*/  owner; struct resource** resources; struct resource_spec* resource_specs; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 

struct resource *
bhndb_host_resource_for_regwin(struct bhndb_host_resources *hr,
    const struct bhndb_regwin *win)
{
	const struct resource_spec *rspecs;

	rspecs = hr->resource_specs;
	for (u_int i = 0; rspecs[i].type != -1; i++) {			
		if (win->res.type != rspecs[i].type)
			continue;

		if (win->res.rid != rspecs[i].rid)
			continue;

		/* Found declared resource */
		return (hr->resources[i]);
	}

	device_printf(hr->owner, "missing regwin resource spec "
	    "(type=%d, rid=%d)\n", win->res.type, win->res.rid);

	return (NULL);
}