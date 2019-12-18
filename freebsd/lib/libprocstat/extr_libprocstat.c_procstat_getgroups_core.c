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
struct procstat_core {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_TYPE_GROUPS ; 
 int /*<<< orphan*/ * procstat_core_get (struct procstat_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static gid_t *
procstat_getgroups_core(struct procstat_core *core, unsigned int *cntp)
{
	size_t len;
	gid_t *groups;

	groups = procstat_core_get(core, PSC_TYPE_GROUPS, NULL, &len);
	if (groups == NULL)
		return (NULL);
	*cntp = len / sizeof(gid_t);
	return (groups);
}