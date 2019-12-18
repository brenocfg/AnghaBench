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
struct TYPE_3__ {size_t cursor; size_t nitems; void** items; } ;
typedef  TYPE_1__ menuframework_s ;

/* Variables and functions */

void *Menu_ItemAtCursor( menuframework_s *m )
{
	if ( m->cursor < 0 || m->cursor >= m->nitems )
		return NULL;

	return m->items[m->cursor];
}