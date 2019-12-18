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
 int /*<<< orphan*/ * added ; 
 int /*<<< orphan*/  cleanup1_doall ; 
 int /*<<< orphan*/  cleanup2_doall ; 
 int /*<<< orphan*/  cleanup3_doall ; 
 int /*<<< orphan*/  lh_ADDED_OBJ_doall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_ADDED_OBJ_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lh_ADDED_OBJ_set_down_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void obj_cleanup_int(void)
{
    if (added == NULL)
        return;
    lh_ADDED_OBJ_set_down_load(added, 0);
    lh_ADDED_OBJ_doall(added, cleanup1_doall); /* zero counters */
    lh_ADDED_OBJ_doall(added, cleanup2_doall); /* set counters */
    lh_ADDED_OBJ_doall(added, cleanup3_doall); /* free objects */
    lh_ADDED_OBJ_free(added);
    added = NULL;
}