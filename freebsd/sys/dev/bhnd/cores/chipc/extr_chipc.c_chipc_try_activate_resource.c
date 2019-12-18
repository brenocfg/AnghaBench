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
struct rman {int dummy; } ;
struct resource {int dummy; } ;
struct chipc_softc {int dummy; } ;
struct chipc_region {TYPE_1__* cr_res; scalar_t__ cr_addr; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_size_t ;
struct TYPE_2__ {int /*<<< orphan*/  res; scalar_t__ direct; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 struct chipc_region* chipc_find_region (struct chipc_softc*,scalar_t__,scalar_t__) ; 
 struct rman* chipc_get_rman (struct chipc_softc*,int) ; 
 int chipc_init_child_resource (struct resource*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  chipc_release_region (struct chipc_softc*,struct chipc_region*,int /*<<< orphan*/ ) ; 
 int chipc_retain_region (struct chipc_softc*,struct chipc_region*,int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 scalar_t__ rman_get_end (struct resource*) ; 
 scalar_t__ rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_is_region_manager (struct resource*,struct rman*) ; 

__attribute__((used)) static int
chipc_try_activate_resource(struct chipc_softc *sc, device_t child, int type,
    int rid, struct resource *r, bool req_direct)
{
	struct rman		*rm;
	struct chipc_region	*cr;
	bhnd_size_t		 cr_offset;
	rman_res_t		 r_start, r_end, r_size;
	int			 error;

	rm = chipc_get_rman(sc, type);
	if (rm == NULL || !rman_is_region_manager(r, rm))
		return (EINVAL);

	r_start = rman_get_start(r);
	r_end = rman_get_end(r);
	r_size = rman_get_size(r);

	/* Find the corresponding chipc region */
	cr = chipc_find_region(sc, r_start, r_end);
	if (cr == NULL)
		return (EINVAL);
	
	/* Calculate subregion offset within the chipc region */
	cr_offset = r_start - cr->cr_addr;

	/* Retain (and activate, if necessary) the chipc region */
	if ((error = chipc_retain_region(sc, cr, RF_ACTIVE)))
		return (error);

	/* Configure child resource with its subregion values. */
	if (cr->cr_res->direct) {
		error = chipc_init_child_resource(r, cr->cr_res->res,
		    cr_offset, r_size);
		if (error)
			goto cleanup;

		/* Mark active */
		if ((error = rman_activate_resource(r)))
			goto cleanup;
	} else if (req_direct) {
		error = ENOMEM;
		goto cleanup;
	}

	return (0);

cleanup:
	chipc_release_region(sc, cr, RF_ACTIVE);
	return (error);
}