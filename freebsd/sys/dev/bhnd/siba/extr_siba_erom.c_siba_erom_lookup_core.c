#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_6__ {scalar_t__ ncores; } ;
struct siba_erom {TYPE_3__ io; } ;
struct bhnd_core_info {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  unit; } ;
struct siba_core_id {struct bhnd_core_info core_info; } ;
struct TYPE_4__ {scalar_t__ core_unit; } ;
struct TYPE_5__ {TYPE_1__ match; } ;
typedef  struct bhnd_core_match {TYPE_2__ m; } const bhnd_core_match ;
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  bhnd_core_matches (struct bhnd_core_info*,struct bhnd_core_match const*) ; 
 int siba_eio_read_core_id (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,struct siba_core_id*) ; 

__attribute__((used)) static int
siba_erom_lookup_core(bhnd_erom_t *erom, const struct bhnd_core_match *desc,
    struct bhnd_core_info *core)
{
	struct siba_erom	*sc;
	struct bhnd_core_match	 imatch;
	int			 error;

	sc = (struct siba_erom *)erom;

	/* We can't determine a core's unit number during the initial scan. */
	imatch = *desc;
	imatch.m.match.core_unit = 0;

	/* Locate the first matching core */
	for (u_int i = 0; i < sc->io.ncores; i++) {
		struct siba_core_id	sid;
		struct bhnd_core_info	ci;

		/* Read the core info */
		if ((error = siba_eio_read_core_id(&sc->io, i, 0, &sid)))
			return (error);

		ci = sid.core_info;

		/* Check for initial match */
		if (!bhnd_core_matches(&ci, &imatch))
			continue;

		/* Re-scan preceding cores to determine the unit number. */
		for (u_int j = 0; j < i; j++) {
			error = siba_eio_read_core_id(&sc->io, j, 0, &sid);
			if (error)
				return (error);

			/* Bump the unit number? */
			if (sid.core_info.vendor == ci.vendor &&
			    sid.core_info.device == ci.device)
				ci.unit++;
		}

		/* Check for full match against now-valid unit number */
		if (!bhnd_core_matches(&ci, desc))
			continue;

		/* Matching core found */
		*core = ci;
		return (0);
	}

	/* Not found */
	return (ENOENT);
}