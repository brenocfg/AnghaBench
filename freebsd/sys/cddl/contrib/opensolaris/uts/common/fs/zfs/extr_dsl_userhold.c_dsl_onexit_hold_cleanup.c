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
struct TYPE_4__ {int /*<<< orphan*/ * zhca_holds; int /*<<< orphan*/  zhca_spa_load_guid; int /*<<< orphan*/  zhca_spaname; } ;
typedef  TYPE_1__ zfs_hold_cleanup_arg_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dataset_user_release_onexit ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_load_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_onexit_add_cb (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_onexit_hold_cleanup(spa_t *spa, nvlist_t *holds, minor_t minor)
{
	zfs_hold_cleanup_arg_t *ca;

	if (minor == 0 || nvlist_empty(holds)) {
		fnvlist_free(holds);
		return;
	}

	ASSERT(spa != NULL);
	ca = kmem_alloc(sizeof (*ca), KM_SLEEP);

	(void) strlcpy(ca->zhca_spaname, spa_name(spa),
	    sizeof (ca->zhca_spaname));
	ca->zhca_spa_load_guid = spa_load_guid(spa);
	ca->zhca_holds = holds;
	VERIFY0(zfs_onexit_add_cb(minor,
	    dsl_dataset_user_release_onexit, ca, NULL));
}