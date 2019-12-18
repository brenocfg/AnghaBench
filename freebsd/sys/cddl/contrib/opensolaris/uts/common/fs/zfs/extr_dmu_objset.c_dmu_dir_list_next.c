#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zap_cursor_t ;
struct TYPE_12__ {int /*<<< orphan*/  za_first_integer; int /*<<< orphan*/  za_name; } ;
typedef  TYPE_3__ zap_attribute_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_13__ {TYPE_1__* os_dsl_dataset; } ;
typedef  TYPE_4__ objset_t ;
struct TYPE_14__ {TYPE_2__* dd_pool; } ;
typedef  TYPE_5__ dsl_dir_t ;
struct TYPE_15__ {scalar_t__ dd_head_dataset_obj; int /*<<< orphan*/  dd_child_dir_zapobj; } ;
struct TYPE_11__ {int /*<<< orphan*/  dp_meta_objset; } ;
struct TYPE_10__ {scalar_t__ ds_object; TYPE_5__* ds_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_7__* dsl_dir_phys (TYPE_5__*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_cursor_advance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_cursor_init_serialized (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zap_cursor_retrieve (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  zap_cursor_serialize (int /*<<< orphan*/ *) ; 

int
dmu_dir_list_next(objset_t *os, int namelen, char *name,
    uint64_t *idp, uint64_t *offp)
{
	dsl_dir_t *dd = os->os_dsl_dataset->ds_dir;
	zap_cursor_t cursor;
	zap_attribute_t attr;

	/* there is no next dir on a snapshot! */
	if (os->os_dsl_dataset->ds_object !=
	    dsl_dir_phys(dd)->dd_head_dataset_obj)
		return (SET_ERROR(ENOENT));

	zap_cursor_init_serialized(&cursor,
	    dd->dd_pool->dp_meta_objset,
	    dsl_dir_phys(dd)->dd_child_dir_zapobj, *offp);

	if (zap_cursor_retrieve(&cursor, &attr) != 0) {
		zap_cursor_fini(&cursor);
		return (SET_ERROR(ENOENT));
	}

	if (strlen(attr.za_name) + 1 > namelen) {
		zap_cursor_fini(&cursor);
		return (SET_ERROR(ENAMETOOLONG));
	}

	(void) strcpy(name, attr.za_name);
	if (idp)
		*idp = attr.za_first_integer;
	zap_cursor_advance(&cursor);
	*offp = zap_cursor_serialize(&cursor);
	zap_cursor_fini(&cursor);

	return (0);
}