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
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static bool
dns_allowed_type(const nvlist_t *limits, const char *type)
{
	const char *name;
	bool notypes;
	void *cookie;

	if (limits == NULL)
		return (true);

	notypes = true;
	cookie = NULL;
	while ((name = nvlist_next(limits, NULL, &cookie)) != NULL) {
		if (strncmp(name, "type", sizeof("type") - 1) != 0)
			continue;
		notypes = false;
		if (strcmp(nvlist_get_string(limits, name), type) == 0)
			return (true);
	}

	/* If there are no types at all, allow any type. */
	if (notypes)
		return (true);

	return (false);
}