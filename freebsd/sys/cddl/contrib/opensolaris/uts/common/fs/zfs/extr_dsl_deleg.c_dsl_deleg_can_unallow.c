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
typedef  scalar_t__ zfs_deleg_who_type_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  longlong_t ;
typedef  int /*<<< orphan*/  idstr ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_DELEG_PERM_ALLOW ; 
 scalar_t__ ZFS_DELEG_USER ; 
 scalar_t__ ZFS_DELEG_USER_SETS ; 
 scalar_t__ crgetuid (int /*<<< orphan*/ *) ; 
 int dsl_deleg_access (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,scalar_t__*) ; 

int
dsl_deleg_can_unallow(char *ddname, nvlist_t *nvp, cred_t *cr)
{
	nvpair_t *whopair = NULL;
	int error;
	char idstr[32];

	if ((error = dsl_deleg_access(ddname, ZFS_DELEG_PERM_ALLOW, cr)) != 0)
		return (error);

	(void) snprintf(idstr, sizeof (idstr), "%lld",
	    (longlong_t)crgetuid(cr));

	while (whopair = nvlist_next_nvpair(nvp, whopair)) {
		zfs_deleg_who_type_t type = nvpair_name(whopair)[0];

		if (type != ZFS_DELEG_USER &&
		    type != ZFS_DELEG_USER_SETS)
			return (SET_ERROR(EPERM));

		if (strcmp(idstr, &nvpair_name(whopair)[3]) != 0)
			return (SET_ERROR(EPERM));
	}
	return (0);
}