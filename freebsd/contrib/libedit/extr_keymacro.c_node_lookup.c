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
typedef  int ssize_t ;
struct TYPE_10__ {scalar_t__ const ch; struct TYPE_10__* sibling; int /*<<< orphan*/  type; int /*<<< orphan*/  val; struct TYPE_10__* next; } ;
typedef  TYPE_2__ keymacro_node_t ;
struct TYPE_9__ {char* buf; } ;
struct TYPE_11__ {TYPE_1__ el_keymacro; } ;
typedef  TYPE_3__ EditLine ;

/* Variables and functions */
 scalar_t__ KEY_BUFSIZ ; 
 int ct_visual_char (char*,scalar_t__,scalar_t__ const) ; 
 int /*<<< orphan*/  keymacro_kprint (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_enum (TYPE_3__*,TYPE_2__*,size_t) ; 

__attribute__((used)) static int
node_lookup(EditLine *el, const wchar_t *str, keymacro_node_t *ptr,
    size_t cnt)
{
	ssize_t used;

	if (ptr == NULL)
		return -1;	/* cannot have null ptr */

	if (!str || *str == 0) {
		/* no more chars in str.  node_enum from here. */
		(void) node_enum(el, ptr, cnt);
		return 0;
	} else {
		/* If match put this char into el->el_keymacro.buf.  Recurse */
		if (ptr->ch == *str) {
			/* match found */
			used = ct_visual_char(el->el_keymacro.buf + cnt,
			    KEY_BUFSIZ - cnt, ptr->ch);
			if (used == -1)
				return -1; /* ran out of buffer space */
			if (ptr->next != NULL)
				/* not yet at leaf */
				return (node_lookup(el, str + 1, ptr->next,
				    (size_t)used + cnt));
			else {
			    /* next node is null so key should be complete */
				if (str[1] == 0) {
					size_t px = cnt + (size_t)used;
					el->el_keymacro.buf[px] = '"';
					el->el_keymacro.buf[px + 1] = '\0';
					keymacro_kprint(el, el->el_keymacro.buf,
					    &ptr->val, ptr->type);
					return 0;
				} else
					return -1;
					/* mismatch -- str still has chars */
			}
		} else {
			/* no match found try sibling */
			if (ptr->sibling)
				return (node_lookup(el, str, ptr->sibling,
				    cnt));
			else
				return -1;
		}
	}
}