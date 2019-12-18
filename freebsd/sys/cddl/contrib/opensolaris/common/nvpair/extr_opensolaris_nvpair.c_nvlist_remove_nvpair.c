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
 int /*<<< orphan*/  nvp_buf_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvp_buf_unlink (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_free (int /*<<< orphan*/ *) ; 
 int nvt_remove_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nvlist_remove_nvpair(nvlist_t *nvl, nvpair_t *nvp)
{
	if (nvl == NULL || nvp == NULL)
		return (EINVAL);

	int err = nvt_remove_nvpair(nvl, nvp);
	if (err != 0)
		return (err);

	nvp_buf_unlink(nvl, nvp);
	nvpair_free(nvp);
	nvp_buf_free(nvl, nvp);
	return (0);
}