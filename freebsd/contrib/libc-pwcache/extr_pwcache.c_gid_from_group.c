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
struct group {int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {scalar_t__ valid; int /*<<< orphan*/  gid; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ GIDC ;

/* Variables and functions */
 int /*<<< orphan*/  GID_SZ ; 
 int /*<<< orphan*/  GNMLEN ; 
 scalar_t__ INVALID ; 
 scalar_t__ VALID ; 
 struct group* _pwcache_getgrnam (char const*) ; 
 int /*<<< orphan*/  _pwcache_setgroupent (int) ; 
 int /*<<< orphan*/  gropn ; 
 TYPE_1__** grptb ; 
 scalar_t__ grptb_start () ; 
 scalar_t__ malloc (int) ; 
 int st_hash (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct group* stub2 (char const*) ; 
 struct group* stub3 (char const*) ; 

int
gid_from_group(const char *name, gid_t *gid)
{
	struct group *gr;
	GIDC *ptr, **pptr;
	size_t namelen;

	/*
	 * return -1 for mangled names
	 */
	if (name == NULL || ((namelen = strlen(name)) == 0))
		return (-1);
	if ((grptb == NULL) && (grptb_start() < 0))
		return (-1);

	/*
	 * look up in hash table, if found and valid return the uid,
	 * if found and invalid, return a -1
	 */
	pptr = grptb + st_hash(name, namelen, GID_SZ);
	ptr = *pptr;

	if ((ptr != NULL) && (ptr->valid > 0) && !strcmp(name, ptr->name)) {
		if (ptr->valid == INVALID)
			return (-1);
		*gid = ptr->gid;
		return (0);
	}

	if (!gropn) {
		if (_pwcache_setgroupent != NULL)
			(*_pwcache_setgroupent)(1);
		++gropn;
	}

	if (ptr == NULL)
		*pptr = ptr = (GIDC *)malloc(sizeof(GIDC));

	/*
	 * no match, look it up, if no match store it as an invalid entry,
	 * or store the matching gid
	 */
	if (ptr == NULL) {
		if ((gr = (*_pwcache_getgrnam)(name)) == NULL)
			return (-1);
		*gid = gr->gr_gid;
		return (0);
	}

	(void)strlcpy(ptr->name, name, GNMLEN);
	if ((gr = (*_pwcache_getgrnam)(name)) == NULL) {
		ptr->valid = INVALID;
		return (-1);
	}
	ptr->valid = VALID;
	*gid = ptr->gid = gr->gr_gid;
	return (0);
}