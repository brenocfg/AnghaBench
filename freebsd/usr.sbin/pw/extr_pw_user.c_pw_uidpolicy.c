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
typedef  scalar_t__ uid_t ;
struct userconf {int min_uid; int max_uid; scalar_t__ reuse_uids; } ;
struct passwd {scalar_t__ pw_uid; } ;
struct bitmap {int dummy; } ;
typedef  scalar_t__ intmax_t ;
struct TYPE_2__ {scalar_t__ checkduplicate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENDPWENT () ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 struct passwd* GETPWENT () ; 
 struct passwd* GETPWUID (scalar_t__) ; 
 int /*<<< orphan*/  SETPWENT () ; 
 struct bitmap bm_alloc (int) ; 
 int /*<<< orphan*/  bm_dealloc (struct bitmap*) ; 
 scalar_t__ bm_firstunset (struct bitmap*) ; 
 scalar_t__ bm_lastset (struct bitmap*) ; 
 int /*<<< orphan*/  bm_setbit (struct bitmap*,scalar_t__) ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static uid_t
pw_uidpolicy(struct userconf * cnf, intmax_t id)
{
	struct passwd  *pwd;
	struct bitmap   bm;
	uid_t           uid = (uid_t) - 1;

	/*
	 * Check the given uid, if any
	 */
	if (id >= 0) {
		uid = (uid_t) id;

		if ((pwd = GETPWUID(uid)) != NULL && conf.checkduplicate)
			errx(EX_DATAERR, "uid `%ju' has already been allocated",
			    (uintmax_t)pwd->pw_uid);
		return (uid);
	}
	/*
	 * We need to allocate the next available uid under one of
	 * two policies a) Grab the first unused uid b) Grab the
	 * highest possible unused uid
	 */
	if (cnf->min_uid >= cnf->max_uid) {	/* Sanity
						 * claus^H^H^H^Hheck */
		cnf->min_uid = 1000;
		cnf->max_uid = 32000;
	}
	bm = bm_alloc(cnf->max_uid - cnf->min_uid + 1);

	/*
	 * Now, let's fill the bitmap from the password file
	 */
	SETPWENT();
	while ((pwd = GETPWENT()) != NULL)
		if (pwd->pw_uid >= (uid_t) cnf->min_uid && pwd->pw_uid <= (uid_t) cnf->max_uid)
			bm_setbit(&bm, pwd->pw_uid - cnf->min_uid);
	ENDPWENT();

	/*
	 * Then apply the policy, with fallback to reuse if necessary
	 */
	if (cnf->reuse_uids || (uid = (uid_t) (bm_lastset(&bm) + cnf->min_uid + 1)) > cnf->max_uid)
		uid = (uid_t) (bm_firstunset(&bm) + cnf->min_uid);

	/*
	 * Another sanity check
	 */
	if (uid < cnf->min_uid || uid > cnf->max_uid)
		errx(EX_SOFTWARE, "unable to allocate a new uid - range fully used");
	bm_dealloc(&bm);
	return (uid);
}