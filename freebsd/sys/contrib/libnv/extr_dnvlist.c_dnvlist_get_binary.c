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
 scalar_t__ nvlist_exists_binary (int /*<<< orphan*/  const*,char const*) ; 
 void* nvlist_get_binary (int /*<<< orphan*/  const*,char const*,size_t*) ; 

const void *
dnvlist_get_binary(const nvlist_t *nvl, const char *name, size_t *sizep,
    const void *defval, size_t defsize)
{
	const void *value;

	if (nvlist_exists_binary(nvl, name))
		value = nvlist_get_binary(nvl, name, sizep);
	else {
		if (sizep != NULL)
			*sizep = defsize;
		value = defval;
	}
	return (value);
}