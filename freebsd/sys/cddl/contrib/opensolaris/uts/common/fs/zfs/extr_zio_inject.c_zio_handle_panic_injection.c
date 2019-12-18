#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_6__ {scalar_t__ zi_type; int /*<<< orphan*/  zi_func; } ;
struct TYPE_7__ {TYPE_1__ zi_record; int /*<<< orphan*/ * zi_spa; } ;
typedef  TYPE_2__ inject_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  inject_handlers ; 
 int /*<<< orphan*/  inject_lock ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
zio_handle_panic_injection(spa_t *spa, char *tag, uint64_t type)
{
	inject_handler_t *handler;

	rw_enter(&inject_lock, RW_READER);

	for (handler = list_head(&inject_handlers); handler != NULL;
	    handler = list_next(&inject_handlers, handler)) {

		if (spa != handler->zi_spa)
			continue;

		if (handler->zi_record.zi_type == type &&
		    strcmp(tag, handler->zi_record.zi_func) == 0)
			panic("Panic requested in function %s\n", tag);
	}

	rw_exit(&inject_lock);
}