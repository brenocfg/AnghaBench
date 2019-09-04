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
struct TYPE_5__ {struct TYPE_5__* s; struct TYPE_5__* u16; struct TYPE_5__* u8tou16; struct TYPE_5__* u16tou8; int /*<<< orphan*/  attrs; } ;
typedef  TYPE_1__ uiAttributedString ;

/* Variables and functions */
 int /*<<< orphan*/  invalidateGraphemes (TYPE_1__*) ; 
 int /*<<< orphan*/  uiprivFree (TYPE_1__*) ; 
 int /*<<< orphan*/  uiprivFreeAttrList (int /*<<< orphan*/ ) ; 

void uiFreeAttributedString(uiAttributedString *s)
{
	uiprivFreeAttrList(s->attrs);
	invalidateGraphemes(s);
	uiprivFree(s->u16tou8);
	uiprivFree(s->u8tou16);
	uiprivFree(s->u16);
	uiprivFree(s->s);
	uiprivFree(s);
}