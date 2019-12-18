#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pi_name; } ;
typedef  TYPE_1__ zprop_index_t ;
struct TYPE_5__ {int pd_proptype; TYPE_1__* pd_table; int /*<<< orphan*/ * pd_colname; } ;
typedef  TYPE_2__ zprop_desc_t ;
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  PROP_TYPE_INDEX 130 
#define  PROP_TYPE_NUMBER 129 
#define  PROP_TYPE_STRING 128 
 int ZFS_PROP_CREATION ; 
 int ZPROP_CONT ; 
 int ZPROP_INVAL ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 int zprop_get_numprops (int /*<<< orphan*/ ) ; 
 TYPE_2__* zprop_get_proptable (int /*<<< orphan*/ ) ; 

size_t
zprop_width(int prop, boolean_t *fixed, zfs_type_t type)
{
	zprop_desc_t *prop_tbl, *pd;
	const zprop_index_t *idx;
	size_t ret;
	int i;

	ASSERT(prop != ZPROP_INVAL && prop != ZPROP_CONT);
	ASSERT(prop < zprop_get_numprops(type));

	prop_tbl = zprop_get_proptable(type);
	pd = &prop_tbl[prop];

	*fixed = B_TRUE;

	/*
	 * Start with the width of the column name.
	 */
	ret = strlen(pd->pd_colname);

	/*
	 * For fixed-width values, make sure the width is large enough to hold
	 * any possible value.
	 */
	switch (pd->pd_proptype) {
	case PROP_TYPE_NUMBER:
		/*
		 * The maximum length of a human-readable number is 5 characters
		 * ("20.4M", for example).
		 */
		if (ret < 5)
			ret = 5;
		/*
		 * 'creation' is handled specially because it's a number
		 * internally, but displayed as a date string.
		 */
		if (prop == ZFS_PROP_CREATION)
			*fixed = B_FALSE;
		break;
	case PROP_TYPE_INDEX:
		idx = prop_tbl[prop].pd_table;
		for (i = 0; idx[i].pi_name != NULL; i++) {
			if (strlen(idx[i].pi_name) > ret)
				ret = strlen(idx[i].pi_name);
		}
		break;

	case PROP_TYPE_STRING:
		*fixed = B_FALSE;
		break;
	}

	return (ret);
}