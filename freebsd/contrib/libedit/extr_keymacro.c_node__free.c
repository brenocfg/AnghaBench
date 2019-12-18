#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* sibling; } ;
typedef  TYPE_1__ keymacro_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  el_free (TYPE_1__*) ; 

__attribute__((used)) static void
node__free(keymacro_node_t *k)
{
	if (k == NULL)
		return;
	node__free(k->sibling);
	node__free(k->next);
	el_free(k);
}