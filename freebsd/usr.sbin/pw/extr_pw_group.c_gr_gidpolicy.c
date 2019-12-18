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
typedef  int /*<<< orphan*/  uintmax_t ;
struct userconf {int min_gid; int max_gid; scalar_t__ reuse_gids; } ;
struct group {int gr_gid; } ;
struct bitmap {int dummy; } ;
typedef  scalar_t__ intmax_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_2__ {scalar_t__ checkduplicate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDGRENT () ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 struct group* GETGRENT () ; 
 struct group* GETGRGID (scalar_t__) ; 
 int /*<<< orphan*/  SETGRENT () ; 
 struct bitmap bm_alloc (int) ; 
 int /*<<< orphan*/  bm_dealloc (struct bitmap*) ; 
 int bm_firstunset (struct bitmap*) ; 
 int /*<<< orphan*/  bm_isset (struct bitmap*,scalar_t__) ; 
 scalar_t__ bm_lastset (struct bitmap*) ; 
 int /*<<< orphan*/  bm_setbit (struct bitmap*,int) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static gid_t
gr_gidpolicy(struct userconf * cnf, intmax_t id)
{
	struct group   *grp;
	struct bitmap   bm;
	gid_t           gid = (gid_t) - 1;

	/*
	 * Check the given gid, if any
	 */
	if (id > 0) {
		gid = (gid_t) id;

		if ((grp = GETGRGID(gid)) != NULL && conf.checkduplicate)
			errx(EX_DATAERR, "gid `%ju' has already been allocated",
			    (uintmax_t)grp->gr_gid);
		return (gid);
	}

	/*
	 * We need to allocate the next available gid under one of
	 * two policies a) Grab the first unused gid b) Grab the
	 * highest possible unused gid
	 */
	if (cnf->min_gid >= cnf->max_gid) {	/* Sanity claus^H^H^H^Hheck */
		cnf->min_gid = 1000;
		cnf->max_gid = 32000;
	}
	bm = bm_alloc(cnf->max_gid - cnf->min_gid + 1);

	/*
	 * Now, let's fill the bitmap from the password file
	 */
	SETGRENT();
	while ((grp = GETGRENT()) != NULL)
		if ((gid_t)grp->gr_gid >= (gid_t)cnf->min_gid &&
		    (gid_t)grp->gr_gid <= (gid_t)cnf->max_gid)
			bm_setbit(&bm, grp->gr_gid - cnf->min_gid);
	ENDGRENT();

	/*
	 * Then apply the policy, with fallback to reuse if necessary
	 */
	if (cnf->reuse_gids)
		gid = (gid_t) (bm_firstunset(&bm) + cnf->min_gid);
	else {
		gid = (gid_t) (bm_lastset(&bm) + 1);
		if (!bm_isset(&bm, gid))
			gid += cnf->min_gid;
		else
			gid = (gid_t) (bm_firstunset(&bm) + cnf->min_gid);
	}

	/*
	 * Another sanity check
	 */
	if (gid < cnf->min_gid || gid > cnf->max_gid)
		errx(EX_SOFTWARE, "unable to allocate a new gid - range fully "
		    "used");
	bm_dealloc(&bm);
	return (gid);
}