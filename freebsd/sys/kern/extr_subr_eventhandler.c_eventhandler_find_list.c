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
 int /*<<< orphan*/  EHL_LOCK (struct eventhandler_list*) ; 
 struct eventhandler_list* _eventhandler_find_list (char const*) ; 
 int /*<<< orphan*/  eventhandler_lists_initted ; 
 int /*<<< orphan*/  eventhandler_mutex ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

struct eventhandler_list *
eventhandler_find_list(const char *name)
{
    struct eventhandler_list	*list;

    if (!eventhandler_lists_initted)
	return(NULL);
    
    /* scan looking for the requested list */
    mtx_lock(&eventhandler_mutex);
    list = _eventhandler_find_list(name);
    if (list != NULL)
	EHL_LOCK(list);
    mtx_unlock(&eventhandler_mutex);
    
    return(list);
}