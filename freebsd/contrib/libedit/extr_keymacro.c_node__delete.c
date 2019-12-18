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
typedef  scalar_t__ wchar_t ;
struct TYPE_4__ {scalar_t__ const ch; struct TYPE_4__* sibling; struct TYPE_4__* next; } ;
typedef  TYPE_1__ keymacro_node_t ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  node__put (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
node__delete(EditLine *el, keymacro_node_t **inptr, const wchar_t *str)
{
	keymacro_node_t *ptr;
	keymacro_node_t *prev_ptr = NULL;

	ptr = *inptr;

	if (ptr->ch != *str) {
		keymacro_node_t *xm;

		for (xm = ptr; xm->sibling != NULL; xm = xm->sibling)
			if (xm->sibling->ch == *str)
				break;
		if (xm->sibling == NULL)
			return 0;
		prev_ptr = xm;
		ptr = xm->sibling;
	}
	if (*++str == '\0') {
		/* we're there */
		if (prev_ptr == NULL)
			*inptr = ptr->sibling;
		else
			prev_ptr->sibling = ptr->sibling;
		ptr->sibling = NULL;
		node__put(el, ptr);
		return 1;
	} else if (ptr->next != NULL &&
	    node__delete(el, &ptr->next, str) == 1) {
		if (ptr->next != NULL)
			return 0;
		if (prev_ptr == NULL)
			*inptr = ptr->sibling;
		else
			prev_ptr->sibling = ptr->sibling;
		ptr->sibling = NULL;
		node__put(el, ptr);
		return 1;
	} else {
		return 0;
	}
}