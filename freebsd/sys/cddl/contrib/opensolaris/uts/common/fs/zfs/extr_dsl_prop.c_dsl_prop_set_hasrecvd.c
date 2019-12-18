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

/* Variables and functions */
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  dsl_prop_get_hasrecvd (char const*) ; 
 int dsl_prop_set_hasrecvd_impl (char const*,int /*<<< orphan*/ ) ; 

int
dsl_prop_set_hasrecvd(const char *dsname)
{
	int error = 0;
	if (!dsl_prop_get_hasrecvd(dsname))
		error = dsl_prop_set_hasrecvd_impl(dsname, ZPROP_SRC_LOCAL);
	return (error);
}