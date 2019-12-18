#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_5__ {scalar_t__ nvl_priv; } ;
typedef  TYPE_1__ nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_remove_nvpair (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvt_lookup_name (TYPE_1__*,char const*) ; 

int
nvlist_remove_all(nvlist_t *nvl, const char *name)
{
	int error = ENOENT;

	if (nvl == NULL || name == NULL || nvl->nvl_priv == 0)
		return (EINVAL);

	nvpair_t *nvp;
	while ((nvp = nvt_lookup_name(nvl, name)) != NULL) {
		VERIFY0(nvlist_remove_nvpair(nvl, nvp));
		error = 0;
	}

	return (error);
}