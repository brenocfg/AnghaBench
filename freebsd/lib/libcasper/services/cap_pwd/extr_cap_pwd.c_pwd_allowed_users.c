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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCAPABLE ; 
#define  NV_TYPE_NUMBER 129 
#define  NV_TYPE_STRING 128 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_get_string (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 int /*<<< orphan*/  pwd_allowed_user (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pwd_allowed_users(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{
	const char *name, *uname;
	void *cookie;
	uid_t uid;
	int type;

	cookie = NULL;
	while ((name = nvlist_next(newlimits, &type, &cookie)) != NULL) {
		switch (type) {
		case NV_TYPE_NUMBER:
			uid = (uid_t)nvlist_get_number(newlimits, name);
			uname = NULL;
			break;
		case NV_TYPE_STRING:
			uid = (uid_t)-1;
			uname = nvlist_get_string(newlimits, name);
			break;
		default:
			return (EINVAL);
		}
		if (!pwd_allowed_user(oldlimits, uname, uid))
			return (ENOTCAPABLE);
	}

	return (0);
}