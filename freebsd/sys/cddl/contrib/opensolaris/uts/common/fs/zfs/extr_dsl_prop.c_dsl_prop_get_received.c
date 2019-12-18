#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  os_dsl_dataset; } ;
typedef  TYPE_1__ objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_prop_getflags_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSL_PROP_GET_LOCAL ; 
 int /*<<< orphan*/  DSL_PROP_GET_RECEIVED ; 
 int /*<<< orphan*/  FTAG ; 
 int dmu_objset_hold (char const*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dmu_objset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int dsl_prop_get_all_ds (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_prop_get_hasrecvd (char const*) ; 

int
dsl_prop_get_received(const char *dsname, nvlist_t **nvp)
{
	objset_t *os;
	int error;

	/*
	 * Received properties are not distinguishable from local properties
	 * until the dataset has received properties on or after
	 * SPA_VERSION_RECVD_PROPS.
	 */
	dsl_prop_getflags_t flags = (dsl_prop_get_hasrecvd(dsname) ?
	    DSL_PROP_GET_RECEIVED : DSL_PROP_GET_LOCAL);

	error = dmu_objset_hold(dsname, FTAG, &os);
	if (error != 0)
		return (error);
	error = dsl_prop_get_all_ds(os->os_dsl_dataset, nvp, flags);
	dmu_objset_rele(os, FTAG);
	return (error);
}