#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct group {char const* gr_name; } ;
typedef  int gid_t ;
struct TYPE_3__ {scalar_t__ valid; int gid; char const* name; } ;
typedef  TYPE_1__ GIDC ;

/* Variables and functions */
 int GID_SZ ; 
 int /*<<< orphan*/  GNMLEN ; 
 scalar_t__ INVALID ; 
 scalar_t__ VALID ; 
 struct group* _pwcache_getgrgid (int) ; 
 int /*<<< orphan*/  _pwcache_setgroupent (int) ; 
 TYPE_1__** gidtb ; 
 scalar_t__ gidtb_start () ; 
 int /*<<< orphan*/  gropn ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  snprintf (char const*,int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  strlcpy (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct group* stub2 (int) ; 

const char *
group_from_gid(gid_t gid, int noname)
{
	struct group *gr;
	GIDC *ptr, **pptr;

	if ((gidtb == NULL) && (gidtb_start() < 0))
		return (NULL);

	/*
	 * see if we have this gid cached
	 */
	pptr = gidtb + (gid % GID_SZ);
	ptr = *pptr;

	if ((ptr != NULL) && (ptr->valid > 0) && (ptr->gid == gid)) {
		/*
		 * have an entry for this gid
		 */
		if (!noname || (ptr->valid == VALID))
			return (ptr->name);
		return (NULL);
	}

	/*
	 * No entry for this gid, we will add it
	 */
	if (!gropn) {
		if (_pwcache_setgroupent != NULL)
			(*_pwcache_setgroupent)(1);
		++gropn;
	}

	if (ptr == NULL)
		*pptr = ptr = (GIDC *)malloc(sizeof(GIDC));

	if ((gr = (*_pwcache_getgrgid)(gid)) == NULL) {
		/*
		 * no match for this gid in the local group file, put in
		 * a string that is the gid in numberic format
		 */
		if (ptr == NULL)
			return (NULL);
		ptr->gid = gid;
		(void)snprintf(ptr->name, GNMLEN, "%lu", (long) gid);
		ptr->valid = INVALID;
		if (noname)
			return (NULL);
	} else {
		/*
		 * there is an entry for this group in the group file
		 */
		if (ptr == NULL)
			return (gr->gr_name);
		ptr->gid = gid;
		(void)strlcpy(ptr->name, gr->gr_name, GNMLEN);
		ptr->valid = VALID;
	}
	return (ptr->name);
}