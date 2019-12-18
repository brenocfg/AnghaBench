#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {scalar_t__ num_elem; size_t head; int max_elem; int /*<<< orphan*/  lock; int /*<<< orphan*/ * elem_array; } ;
typedef  TYPE_1__ pqi_taglist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  INVALID_ELEM ; 
 int /*<<< orphan*/  OS_ACQUIRE_SPINLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_RELEASE_SPINLOCK (int /*<<< orphan*/ *) ; 

uint32_t pqisrc_get_tag(pqi_taglist_t *taglist)
{
	uint32_t elem = INVALID_ELEM;

	/*DBG_FUNC("IN\n");*/

	OS_ACQUIRE_SPINLOCK(&taglist->lock);

	ASSERT(taglist->num_elem > 0);

	if (taglist->num_elem > 0) {
		elem = taglist->elem_array[taglist->head];
		taglist->num_elem--;
		taglist->head = (taglist->head + 1) % taglist->max_elem;
	}

	OS_RELEASE_SPINLOCK(&taglist->lock);

	/*DBG_FUNC("OUT got %d\n", elem);*/
	return elem;
}