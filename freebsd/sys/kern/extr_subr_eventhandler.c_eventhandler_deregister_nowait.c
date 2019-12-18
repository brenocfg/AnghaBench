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
typedef  int /*<<< orphan*/  eventhandler_tag ;

/* Variables and functions */
 int /*<<< orphan*/  _eventhandler_deregister (struct eventhandler_list*,int /*<<< orphan*/ ,int) ; 

void
eventhandler_deregister_nowait(struct eventhandler_list *list,
    eventhandler_tag tag)
{

	_eventhandler_deregister(list, tag, false);
}