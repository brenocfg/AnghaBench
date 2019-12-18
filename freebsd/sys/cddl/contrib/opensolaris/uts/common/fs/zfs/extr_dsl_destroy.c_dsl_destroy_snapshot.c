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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int dsl_destroy_snapshots_nvl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 

int
dsl_destroy_snapshot(const char *name, boolean_t defer)
{
	int error;
	nvlist_t *nvl = fnvlist_alloc();
	nvlist_t *errlist = fnvlist_alloc();

	fnvlist_add_boolean(nvl, name);
	error = dsl_destroy_snapshots_nvl(nvl, defer, errlist);
	fnvlist_free(errlist);
	fnvlist_free(nvl);
	return (error);
}