#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eventhandler_list {int dummy; } ;
struct TYPE_2__ {int ee_priority; void* ee_arg; } ;
struct eventhandler_entry_generic {TYPE_1__ ee; void* func; } ;
typedef  int /*<<< orphan*/  eventhandler_tag ;

/* Variables and functions */
 int /*<<< orphan*/  M_EVENTHANDLER ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  eventhandler_register_internal (struct eventhandler_list*,char const*,TYPE_1__*) ; 
 struct eventhandler_entry_generic* malloc (int,int /*<<< orphan*/ ,int) ; 

eventhandler_tag
eventhandler_register(struct eventhandler_list *list, const char *name, 
		      void *func, void *arg, int priority)
{
    struct eventhandler_entry_generic	*eg;
    
    /* allocate an entry for this handler, populate it */
    eg = malloc(sizeof(struct eventhandler_entry_generic), M_EVENTHANDLER,
	M_WAITOK | M_ZERO);
    eg->func = func;
    eg->ee.ee_arg = arg;
    eg->ee.ee_priority = priority;

    return (eventhandler_register_internal(list, name, &eg->ee));
}