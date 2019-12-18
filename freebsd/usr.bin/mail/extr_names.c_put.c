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
struct name {struct name* n_blink; struct name* n_flink; } ;

/* Variables and functions */

struct name *
put(struct name *list, struct name *node)
{
	node->n_flink = list;
	node->n_blink = NULL;
	if (list != NULL)
		list->n_blink = node;
	return (node);
}