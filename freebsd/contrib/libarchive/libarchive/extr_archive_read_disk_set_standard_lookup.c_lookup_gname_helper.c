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
struct name_cache {int dummy; } ;
struct group {int /*<<< orphan*/  gr_name; } ;
typedef  scalar_t__ id_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 char const* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
lookup_gname_helper(struct name_cache *cache, id_t id)
{
	struct group	*result;
	(void)cache; /* UNUSED */

	result = getgrgid((gid_t)id);

	if (result == NULL)
		return (NULL);

	return strdup(result->gr_name);
}