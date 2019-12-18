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
struct event {int dummy; } ;
struct TYPE_5__ {scalar_t__ n; } ;
typedef  TYPE_1__ min_heap_t ;

/* Variables and functions */
 scalar_t__ min_heap_reserve_ (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  min_heap_shift_up_ (TYPE_1__*,int /*<<< orphan*/ ,struct event*) ; 

int min_heap_push_(min_heap_t* s, struct event* e)
{
	if (min_heap_reserve_(s, s->n + 1))
		return -1;
	min_heap_shift_up_(s, s->n++, e);
	return 0;
}