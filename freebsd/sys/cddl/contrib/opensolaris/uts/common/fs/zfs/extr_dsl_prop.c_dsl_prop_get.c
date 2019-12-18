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
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int dmu_objset_hold (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsl_prop_get_ds (int /*<<< orphan*/ ,char const*,int,int,void*,char*) ; 

int
dsl_prop_get(const char *dsname, const char *propname,
    int intsz, int numints, void *buf, char *setpoint)
{
	objset_t *os;
	int error;

	error = dmu_objset_hold(dsname, FTAG, &os);
	if (error != 0)
		return (error);

	error = dsl_prop_get_ds(dmu_objset_ds(os), propname,
	    intsz, numints, buf, setpoint);

	dmu_objset_rele(os, FTAG);
	return (error);
}