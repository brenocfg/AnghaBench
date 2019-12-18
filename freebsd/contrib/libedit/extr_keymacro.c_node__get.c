#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
struct TYPE_5__ {int /*<<< orphan*/ * str; } ;
struct TYPE_6__ {int /*<<< orphan*/ * sibling; int /*<<< orphan*/ * next; TYPE_1__ val; int /*<<< orphan*/  type; int /*<<< orphan*/  ch; } ;
typedef  TYPE_2__ keymacro_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  XK_NOD ; 
 TYPE_2__* el_malloc (int) ; 

__attribute__((used)) static keymacro_node_t *
node__get(wint_t ch)
{
	keymacro_node_t *ptr;

	ptr = el_malloc(sizeof(*ptr));
	if (ptr == NULL)
		return NULL;
	ptr->ch = ch;
	ptr->type = XK_NOD;
	ptr->val.str = NULL;
	ptr->next = NULL;
	ptr->sibling = NULL;
	return ptr;
}