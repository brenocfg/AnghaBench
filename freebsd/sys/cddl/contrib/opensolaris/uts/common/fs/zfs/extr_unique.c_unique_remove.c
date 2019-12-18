#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  un_value; } ;
typedef  TYPE_1__ unique_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unique_avl ; 
 int /*<<< orphan*/  unique_mtx ; 

void
unique_remove(uint64_t value)
{
	unique_t un_tofind;
	unique_t *un;

	un_tofind.un_value = value;
	mutex_enter(&unique_mtx);
	un = avl_find(&unique_avl, &un_tofind, NULL);
	if (un != NULL) {
		avl_remove(&unique_avl, un);
		kmem_free(un, sizeof (unique_t));
	}
	mutex_exit(&unique_mtx);
}