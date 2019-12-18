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
typedef  int uid_t ;
struct passwd {char const* pw_name; } ;
struct TYPE_3__ {scalar_t__ valid; int uid; char const* name; } ;
typedef  TYPE_1__ UIDC ;

/* Variables and functions */
 scalar_t__ INVALID ; 
 int UID_SZ ; 
 int /*<<< orphan*/  UNMLEN ; 
 scalar_t__ VALID ; 
 struct passwd* _pwcache_getpwuid (int) ; 
 int /*<<< orphan*/  _pwcache_setpassent (int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pwopn ; 
 int /*<<< orphan*/  snprintf (char const*,int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  strlcpy (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct passwd* stub2 (int) ; 
 TYPE_1__** uidtb ; 
 scalar_t__ uidtb_start () ; 

const char *
user_from_uid(uid_t uid, int noname)
{
	struct passwd *pw;
	UIDC *ptr, **pptr;

	if ((uidtb == NULL) && (uidtb_start() < 0))
		return (NULL);

	/*
	 * see if we have this uid cached
	 */
	pptr = uidtb + (uid % UID_SZ);
	ptr = *pptr;

	if ((ptr != NULL) && (ptr->valid > 0) && (ptr->uid == uid)) {
		/*
		 * have an entry for this uid
		 */
		if (!noname || (ptr->valid == VALID))
			return (ptr->name);
		return (NULL);
	}

	/*
	 * No entry for this uid, we will add it
	 */
	if (!pwopn) {
		if (_pwcache_setpassent != NULL)
			(*_pwcache_setpassent)(1);
		++pwopn;
	}

	if (ptr == NULL)
		*pptr = ptr = (UIDC *)malloc(sizeof(UIDC));

	if ((pw = (*_pwcache_getpwuid)(uid)) == NULL) {
		/*
		 * no match for this uid in the local password file
		 * a string that is the uid in numeric format
		 */
		if (ptr == NULL)
			return (NULL);
		ptr->uid = uid;
		(void)snprintf(ptr->name, UNMLEN, "%lu", (long) uid);
		ptr->valid = INVALID;
		if (noname)
			return (NULL);
	} else {
		/*
		 * there is an entry for this uid in the password file
		 */
		if (ptr == NULL)
			return (pw->pw_name);
		ptr->uid = uid;
		(void)strlcpy(ptr->name, pw->pw_name, UNMLEN);
		ptr->valid = VALID;
	}
	return (ptr->name);
}