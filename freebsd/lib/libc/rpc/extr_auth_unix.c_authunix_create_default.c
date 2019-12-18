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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  machname ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  MAXHOSTNAMELEN ; 
 int NGRPS ; 
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * authunix_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 int getgroups (long,int /*<<< orphan*/ *) ; 
 int gethostname (char*,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

AUTH *
authunix_create_default(void)
{
	AUTH *auth;
	int ngids;
	long ngids_max;
	char machname[MAXHOSTNAMELEN + 1];
	uid_t uid;
	gid_t gid;
	gid_t *gids;

	ngids_max = sysconf(_SC_NGROUPS_MAX) + 1;
	gids = malloc(sizeof(gid_t) * ngids_max);
	if (gids == NULL)
		return (NULL);

	if (gethostname(machname, sizeof machname) == -1)
		abort();
	machname[sizeof(machname) - 1] = 0;
	uid = geteuid();
	gid = getegid();
	if ((ngids = getgroups(ngids_max, gids)) < 0)
		abort();
	if (ngids > NGRPS)
		ngids = NGRPS;
	/* XXX: interface problem; we should translate from uid_t and gid_t */
	auth = authunix_create(machname, uid, gid, ngids, gids);
	free(gids);
	return (auth);
}