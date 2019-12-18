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
typedef  scalar_t__ u_int ;
struct siba_erom {int /*<<< orphan*/  io; } ;
struct TYPE_2__ {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  unit; } ;
struct siba_core_id {TYPE_1__ core_info; } ;

/* Variables and functions */
 int siba_eio_read_core_id (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct siba_core_id*) ; 

int
siba_erom_get_core_id(struct siba_erom *sc, u_int core_idx,
    struct siba_core_id *result)
{
	struct siba_core_id	sid;
	int			error;

	/* Fetch the core info, assuming a unit number of 0 */
	if ((error = siba_eio_read_core_id(&sc->io, core_idx, 0, &sid)))
		return (error);

	/* Scan preceding cores to determine the real unit number. */
	for (u_int i = 0; i < core_idx; i++) {
		struct siba_core_id prev;

		if ((error = siba_eio_read_core_id(&sc->io, i, 0, &prev)))
			return (error);

		/* Bump the unit number? */
		if (sid.core_info.vendor == prev.core_info.vendor &&
		    sid.core_info.device == prev.core_info.device)
			sid.core_info.unit++;
	}

	*result = sid;
	return (0);
}