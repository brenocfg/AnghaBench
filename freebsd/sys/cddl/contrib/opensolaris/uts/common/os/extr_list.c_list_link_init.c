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
struct TYPE_3__ {int /*<<< orphan*/ * list_prev; int /*<<< orphan*/ * list_next; } ;
typedef  TYPE_1__ list_node_t ;

/* Variables and functions */

void
list_link_init(list_node_t *link)
{
	link->list_next = NULL;
	link->list_prev = NULL;
}