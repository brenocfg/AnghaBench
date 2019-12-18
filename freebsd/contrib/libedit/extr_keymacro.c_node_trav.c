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
typedef  char wchar_t ;
struct TYPE_5__ {int /*<<< orphan*/ * str; } ;
typedef  TYPE_1__ keymacro_value_t ;
struct TYPE_6__ {char ch; scalar_t__ type; struct TYPE_6__* sibling; TYPE_1__ val; struct TYPE_6__* next; } ;
typedef  TYPE_2__ keymacro_node_t ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 scalar_t__ XK_CMD ; 
 int XK_NOD ; 
 int XK_STR ; 
 int el_wgetc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
node_trav(EditLine *el, keymacro_node_t *ptr, wchar_t *ch,
    keymacro_value_t *val)
{

	if (ptr->ch == *ch) {
		/* match found */
		if (ptr->next) {
			/* key not complete so get next char */
			if (el_wgetc(el, ch) != 1)
				return XK_NOD;
			return node_trav(el, ptr->next, ch, val);
		} else {
			*val = ptr->val;
			if (ptr->type != XK_CMD)
				*ch = '\0';
			return ptr->type;
		}
	} else {
		/* no match found here */
		if (ptr->sibling) {
			/* try next sibling */
			return node_trav(el, ptr->sibling, ch, val);
		} else {
			/* no next sibling -- mismatch */
			val->str = NULL;
			return XK_STR;
		}
	}
}