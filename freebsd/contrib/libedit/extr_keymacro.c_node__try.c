#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
struct TYPE_9__ {int /*<<< orphan*/ * str; } ;
typedef  TYPE_1__ keymacro_value_t ;
struct TYPE_10__ {scalar_t__ const ch; int type; struct TYPE_10__* next; TYPE_1__ val; struct TYPE_10__* sibling; } ;
typedef  TYPE_2__ keymacro_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  el_errfile; } ;
typedef  TYPE_3__ EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ABORT (int /*<<< orphan*/ ) ; 
#define  XK_CMD 130 
#define  XK_NOD 129 
#define  XK_STR 128 
 int /*<<< orphan*/  el_free (int /*<<< orphan*/ *) ; 
 void* node__get (scalar_t__ const) ; 
 int /*<<< orphan*/  node__put (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * wcsdup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
node__try(EditLine *el, keymacro_node_t *ptr, const wchar_t *str,
    keymacro_value_t *val, int ntype)
{

	if (ptr->ch != *str) {
		keymacro_node_t *xm;

		for (xm = ptr; xm->sibling != NULL; xm = xm->sibling)
			if (xm->sibling->ch == *str)
				break;
		if (xm->sibling == NULL)
			xm->sibling = node__get(*str);	/* setup new node */
		ptr = xm->sibling;
	}
	if (*++str == '\0') {
		/* we're there */
		if (ptr->next != NULL) {
			node__put(el, ptr->next);
				/* lose longer keys with this prefix */
			ptr->next = NULL;
		}
		switch (ptr->type) {
		case XK_CMD:
		case XK_NOD:
			break;
		case XK_STR:
			if (ptr->val.str)
				el_free(ptr->val.str);
			break;
		default:
			EL_ABORT((el->el_errfile, "Bad XK_ type %d\n",
			    ptr->type));
			break;
		}

		switch (ptr->type = ntype) {
		case XK_CMD:
			ptr->val = *val;
			break;
		case XK_STR:
			if ((ptr->val.str = wcsdup(val->str)) == NULL)
				return -1;
			break;
		default:
			EL_ABORT((el->el_errfile, "Bad XK_ type %d\n", ntype));
			break;
		}
	} else {
		/* still more chars to go */
		if (ptr->next == NULL)
			ptr->next = node__get(*str);	/* setup new node */
		(void) node__try(el, ptr->next, str, val, ntype);
	}
	return 0;
}