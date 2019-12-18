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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NVP_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NVP_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NVP_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NVP_VALUE (int /*<<< orphan*/ *) ; 
 int nvlist_add_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nvlist_add_nvpair(nvlist_t *nvl, nvpair_t *nvp)
{
	if (nvl == NULL || nvp == NULL)
		return (EINVAL);

	return (nvlist_add_common(nvl, NVP_NAME(nvp), NVP_TYPE(nvp),
	    NVP_NELEM(nvp), NVP_VALUE(nvp)));
}