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
struct eventhandler_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct eventhandler_list* eventhandler_find_or_create_list (char const*) ; 
 int /*<<< orphan*/  eventhandler_lists_initted ; 
 int /*<<< orphan*/  eventhandler_mutex ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

struct eventhandler_list *
eventhandler_create_list(const char *name)
{
	struct eventhandler_list *list;

	KASSERT(eventhandler_lists_initted,
	    ("eventhandler list created too early"));

	mtx_lock(&eventhandler_mutex);
	list = eventhandler_find_or_create_list(name);
	mtx_unlock(&eventhandler_mutex);

	return (list);
}