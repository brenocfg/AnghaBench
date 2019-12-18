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
typedef  int /*<<< orphan*/  zprop_source_t ;
struct TYPE_4__ {scalar_t__ zc_nvlist_dst; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_iflags; int /*<<< orphan*/  zc_nvlist_src_size; int /*<<< orphan*/  zc_nvlist_src; scalar_t__ zc_cookie; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPROP_SRC_LOCAL ; 
 int /*<<< orphan*/  ZPROP_SRC_RECEIVED ; 
 int /*<<< orphan*/  clear_received_props (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_prop_get_received (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dsl_prop_set_hasrecvd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int get_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_nvlist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_set_prop_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_ioc_set_prop(zfs_cmd_t *zc)
{
	nvlist_t *nvl;
	boolean_t received = zc->zc_cookie;
	zprop_source_t source = (received ? ZPROP_SRC_RECEIVED :
	    ZPROP_SRC_LOCAL);
	nvlist_t *errors;
	int error;

	if ((error = get_nvlist(zc->zc_nvlist_src, zc->zc_nvlist_src_size,
	    zc->zc_iflags, &nvl)) != 0)
		return (error);

	if (received) {
		nvlist_t *origprops;

		if (dsl_prop_get_received(zc->zc_name, &origprops) == 0) {
			(void) clear_received_props(zc->zc_name,
			    origprops, nvl);
			nvlist_free(origprops);
		}

		error = dsl_prop_set_hasrecvd(zc->zc_name);
	}

	errors = fnvlist_alloc();
	if (error == 0)
		error = zfs_set_prop_nvlist(zc->zc_name, source, nvl, errors);

	if (zc->zc_nvlist_dst != 0 && errors != NULL) {
		(void) put_nvlist(zc, errors);
	}

	nvlist_free(errors);
	nvlist_free(nvl);
	return (error);
}