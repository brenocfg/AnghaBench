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
typedef  TYPE_1__* mqd_t ;
struct TYPE_4__ {int oshandle; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sigev_delete_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int __sys_close (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int
__mq_close(mqd_t mqd)
{
	int h;

	if (mqd->node != NULL) {
		__sigev_list_lock();
		__sigev_delete_node(mqd->node);
		__sigev_list_unlock();
	}
	h = mqd->oshandle;
	free(mqd);
	return (__sys_close(h));
}