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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;
struct TYPE_3__ {scalar_t__ valid; int /*<<< orphan*/  uid; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ UIDC ;

/* Variables and functions */
 scalar_t__ INVALID ; 
 int /*<<< orphan*/  UNMLEN ; 
 int /*<<< orphan*/  UNM_SZ ; 
 scalar_t__ VALID ; 
 struct passwd* _pwcache_getpwnam (char const*) ; 
 int /*<<< orphan*/  _pwcache_setpassent (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pwopn ; 
 int st_hash (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct passwd* stub2 (char const*) ; 
 struct passwd* stub3 (char const*) ; 
 TYPE_1__** usrtb ; 
 scalar_t__ usrtb_start () ; 

int
uid_from_user(const char *name, uid_t *uid)
{
	struct passwd *pw;
	UIDC *ptr, **pptr;
	size_t namelen;

	/*
	 * return -1 for mangled names
	 */
	if (name == NULL || ((namelen = strlen(name)) == 0))
		return (-1);
	if ((usrtb == NULL) && (usrtb_start() < 0))
		return (-1);

	/*
	 * look up in hash table, if found and valid return the uid,
	 * if found and invalid, return a -1
	 */
	pptr = usrtb + st_hash(name, namelen, UNM_SZ);
	ptr = *pptr;

	if ((ptr != NULL) && (ptr->valid > 0) && !strcmp(name, ptr->name)) {
		if (ptr->valid == INVALID)
			return (-1);
		*uid = ptr->uid;
		return (0);
	}

	if (!pwopn) {
		if (_pwcache_setpassent != NULL)
			(*_pwcache_setpassent)(1);
		++pwopn;
	}

	if (ptr == NULL)
		*pptr = ptr = (UIDC *)malloc(sizeof(UIDC));

	/*
	 * no match, look it up, if no match store it as an invalid entry,
	 * or store the matching uid
	 */
	if (ptr == NULL) {
		if ((pw = (*_pwcache_getpwnam)(name)) == NULL)
			return (-1);
		*uid = pw->pw_uid;
		return (0);
	}
	(void)strlcpy(ptr->name, name, UNMLEN);
	if ((pw = (*_pwcache_getpwnam)(name)) == NULL) {
		ptr->valid = INVALID;
		return (-1);
	}
	ptr->valid = VALID;
	*uid = ptr->uid = pw->pw_uid;
	return (0);
}