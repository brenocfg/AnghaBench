#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zinject_record_t ;
struct TYPE_5__ {int zi_id; int /*<<< orphan*/  zi_spa; int /*<<< orphan*/  zi_record; } ;
typedef  TYPE_1__ inject_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  RW_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inject_handlers ; 
 int /*<<< orphan*/  inject_lock ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

int
zio_inject_list_next(int *id, char *name, size_t buflen,
    zinject_record_t *record)
{
	inject_handler_t *handler;
	int ret;

	mutex_enter(&spa_namespace_lock);
	rw_enter(&inject_lock, RW_READER);

	for (handler = list_head(&inject_handlers); handler != NULL;
	    handler = list_next(&inject_handlers, handler))
		if (handler->zi_id > *id)
			break;

	if (handler) {
		*record = handler->zi_record;
		*id = handler->zi_id;
		(void) strncpy(name, spa_name(handler->zi_spa), buflen);
		ret = 0;
	} else {
		ret = SET_ERROR(ENOENT);
	}

	rw_exit(&inject_lock);
	mutex_exit(&spa_namespace_lock);

	return (ret);
}