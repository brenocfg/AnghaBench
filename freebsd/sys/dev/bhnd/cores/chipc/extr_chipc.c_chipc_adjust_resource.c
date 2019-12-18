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
struct rman {int dummy; } ;
struct resource {int dummy; } ;
struct chipc_softc {int dummy; } ;
struct chipc_region {scalar_t__ cr_addr; scalar_t__ cr_end; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int bus_generic_adjust_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*,scalar_t__,scalar_t__) ; 
 struct chipc_region* chipc_find_region (struct chipc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rman* chipc_get_rman (struct chipc_softc*,int) ; 
 struct chipc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int rman_adjust_resource (struct resource*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rman_get_end (struct resource*) ; 
 int /*<<< orphan*/  rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 

__attribute__((used)) static int
chipc_adjust_resource(device_t dev, device_t child, int type,
    struct resource *r, rman_res_t start, rman_res_t end)
{
	struct chipc_softc		*sc;
	struct chipc_region		*cr;
	struct rman			*rm;
	
	sc = device_get_softc(dev);

	/* Handled by parent bus? */
	rm = chipc_get_rman(sc, type);
	if (rm == NULL || !rman_is_region_manager(r, rm)) {
		return (bus_generic_adjust_resource(dev, child, type, r, start,
		    end));
	}

	/* The range is limited to the existing region mapping */
	cr = chipc_find_region(sc, rman_get_start(r), rman_get_end(r));
	if (cr == NULL)
		return (EINVAL);
	
	if (end <= start)
		return (EINVAL);

	if (start < cr->cr_addr || end > cr->cr_end)
		return (EINVAL);

	/* Range falls within the existing region */
	return (rman_adjust_resource(r, start, end));
}