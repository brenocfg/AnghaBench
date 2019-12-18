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
struct Strbuf {size_t len; int /*<<< orphan*/  s; } ;
struct TYPE_3__ {struct TYPE_3__* sibling; struct TYPE_3__* next; int /*<<< orphan*/  type; int /*<<< orphan*/  val; int /*<<< orphan*/  ch; } ;
typedef  TYPE_1__ XmapNode ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,char) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int /*<<< orphan*/  printOne (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unparsech (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Enumerate(struct Strbuf *buf, const XmapNode *ptr)
{
    size_t old_len;

    if (ptr == NULL) {
#ifdef DEBUG_EDIT
	xprintf(CGETS(9, 6, "Enumerate: BUG!! Null ptr passed\n!"));
#endif
	return;
    }

    old_len = buf->len;
    unparsech(buf, ptr->ch); /* put this char at end of string */
    if (ptr->next == NULL) {
	/* print this Xkey and function */
	Strbuf_append1(buf, '"');
	Strbuf_terminate(buf);
	printOne(buf->s, &ptr->val, ptr->type);
    }
    else
	Enumerate(buf, ptr->next);

    /* go to sibling if there is one */
    if (ptr->sibling) {
	buf->len = old_len;
	Enumerate(buf, ptr->sibling);
    }
}