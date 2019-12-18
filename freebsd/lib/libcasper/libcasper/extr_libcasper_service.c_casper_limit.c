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
 int /*<<< orphan*/  casper_allowed_service (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 

__attribute__((used)) static int
casper_limit(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{
	const char *name;
	int type;
	void *cookie;

	cookie = NULL;
	while ((name = nvlist_next(newlimits, &type, &cookie)) != NULL) {
		if (type != NV_TYPE_NULL)
			return (EINVAL);
		if (!casper_allowed_service(oldlimits, name))
			return (ENOTCAPABLE);
	}

	return (0);
}