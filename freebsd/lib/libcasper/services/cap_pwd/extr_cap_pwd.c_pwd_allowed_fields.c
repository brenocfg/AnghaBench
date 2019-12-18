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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCAPABLE ; 
 int NV_TYPE_NULL ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 int /*<<< orphan*/  pwd_allowed_field (int /*<<< orphan*/  const*,char const*) ; 

__attribute__((used)) static int
pwd_allowed_fields(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{
	const char *name;
	void *cookie;
	int type;

	cookie = NULL;
	while ((name = nvlist_next(newlimits, &type, &cookie)) != NULL) {
		if (type != NV_TYPE_NULL)
			return (EINVAL);
		if (!pwd_allowed_field(oldlimits, name))
			return (ENOTCAPABLE);
	}

	return (0);
}