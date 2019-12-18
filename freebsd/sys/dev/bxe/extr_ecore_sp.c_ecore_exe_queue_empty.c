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
struct ecore_exe_queue_obj {int /*<<< orphan*/  pending_comp; int /*<<< orphan*/  exe_queue; } ;

/* Variables and functions */
 int ECORE_LIST_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline bool ecore_exe_queue_empty(struct ecore_exe_queue_obj *o)
{
	bool empty = ECORE_LIST_IS_EMPTY(&o->exe_queue);

	/* Don't reorder!!! */
	mb();

	return empty && ECORE_LIST_IS_EMPTY(&o->pending_comp);
}