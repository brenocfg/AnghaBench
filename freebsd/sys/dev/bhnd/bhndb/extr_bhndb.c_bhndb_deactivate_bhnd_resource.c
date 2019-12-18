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
struct bhnd_resource {int direct; int /*<<< orphan*/  res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int RF_ACTIVE ; 
 int rman_get_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhndb_deactivate_bhnd_resource(device_t dev, device_t child,
    int type, int rid, struct bhnd_resource *r)
{
	int error;

	/* Indirect resources don't require activation */
	if (!r->direct)
		return (0);

	KASSERT(rman_get_flags(r->res) & RF_ACTIVE,
	    ("RF_ACTIVE not set on direct resource"));

	/* Perform deactivation */
	error = BUS_DEACTIVATE_RESOURCE(dev, child, type, rid, r->res);
	if (!error)
		r->direct = false;

	return (error);
}