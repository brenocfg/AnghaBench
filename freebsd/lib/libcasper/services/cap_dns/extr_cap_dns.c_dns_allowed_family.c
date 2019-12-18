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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int AF_UNSPEC ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static bool
dns_allowed_family(const nvlist_t *limits, int family)
{
	const char *name;
	bool nofamilies;
	void *cookie;

	if (limits == NULL)
		return (true);

	nofamilies = true;
	cookie = NULL;
	while ((name = nvlist_next(limits, NULL, &cookie)) != NULL) {
		if (strncmp(name, "family", sizeof("family") - 1) != 0)
			continue;
		nofamilies = false;
		if (family == AF_UNSPEC)
			continue;
		if (nvlist_get_number(limits, name) == (uint64_t)family)
			return (true);
	}

	/* If there are no families at all, allow any family. */
	if (nofamilies)
		return (true);

	return (false);
}