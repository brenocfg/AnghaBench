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
typedef  int /*<<< orphan*/  ocs_lock_t ;
typedef  int /*<<< orphan*/  ocs_list_t ;
typedef  int /*<<< orphan*/  ocs_hw_sequence_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ocs_hw_sequence_t *
ocs_frame_next(ocs_list_t *pend_list, ocs_lock_t *list_lock)
{
	ocs_hw_sequence_t *frame = NULL;

	ocs_lock(list_lock);
		frame = ocs_list_remove_head(pend_list);
	ocs_unlock(list_lock);
	return frame;
}