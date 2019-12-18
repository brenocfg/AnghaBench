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
struct TYPE_5__ {scalar_t__ no_of_elements; int /*<<< orphan*/ * front; int /*<<< orphan*/  get_order; } ;
typedef  TYPE_1__ queue ;
typedef  int /*<<< orphan*/  q_order_func ;

/* Variables and functions */
 TYPE_1__* debug_erealloc (int /*<<< orphan*/ *,int,char const*,int) ; 
 TYPE_1__* emalloc (int) ; 

queue *debug_create_priority_queue(
	q_order_func	get_order
#ifdef _CRTDBG_MAP_ALLOC
	, const char *	sourcefile
	, int		line_num
#endif	
	)
{
	queue *my_queue;

#ifndef _CRTDBG_MAP_ALLOC
	my_queue = emalloc(sizeof(queue));
#else
	/* preserve original callsite __FILE__ and __LINE__ for leak report */
	my_queue = debug_erealloc(NULL, sizeof(queue), sourcefile, line_num);
#endif
	my_queue->get_order = get_order;
	my_queue->front = NULL;
	my_queue->no_of_elements = 0;

	return my_queue;
}