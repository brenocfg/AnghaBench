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
 int allowed_operations ; 
 char* dnvlist_get_string (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lastname ; 
 int /*<<< orphan*/  nvlist_exists_null (int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
fileargs_allowed(const nvlist_t *limits, const nvlist_t *request, int operation)
{
	const char *name;

	if ((allowed_operations & operation) == 0)
		return (false);

	name = dnvlist_get_string(request, "name", NULL);
	if (name == NULL)
		return (false);

	/* Fast path. */
	if (lastname != NULL && strcmp(name, lastname) == 0)
		return (true);

	if (!nvlist_exists_null(limits, name))
		return (false);

	return (true);
}