#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct Strbuf {int /*<<< orphan*/  s; } ;
struct TYPE_6__ {scalar_t__ ch; struct TYPE_6__* sibling; int /*<<< orphan*/  type; int /*<<< orphan*/  val; struct TYPE_6__* next; } ;
typedef  TYPE_1__ XmapNode ;
struct TYPE_7__ {int len; scalar_t__* buf; } ;
typedef  TYPE_2__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  Enumerate (struct Strbuf*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,char) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int /*<<< orphan*/  printOne (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unparsech (struct Strbuf*,scalar_t__) ; 

__attribute__((used)) static int
Lookup(struct Strbuf *buf, const CStr *str, const XmapNode *ptr)
{
    if (ptr == NULL)
	return (-1);		/* cannot have null ptr */

    if (str->len == 0) {
	/* no more chars in string.  Enumerate from here. */
	Enumerate(buf, ptr);
	return (0);
    }
    else {
	/* If match put this char into buf.  Recurse */
	if (ptr->ch == *(str->buf)) {
	    /* match found */
	    unparsech(buf, ptr->ch);
	    if (ptr->next != NULL) {
		/* not yet at leaf */
		CStr tstr;
		tstr.buf = str->buf + 1;
		tstr.len = str->len - 1;
		return (Lookup(buf, &tstr, ptr->next));
	    }
	    else {
		/* next node is null so key should be complete */
		if (str->len == 1) {
		    Strbuf_append1(buf, '"');
		    Strbuf_terminate(buf);
		    printOne(buf->s, &ptr->val, ptr->type);
		    return (0);
		}
		else
		    return (-1);/* mismatch -- string still has chars */
	    }
	}
	else {
	    /* no match found try sibling */
	    if (ptr->sibling)
		return (Lookup(buf, str, ptr->sibling));
	    else
		return (-1);
	}
    }
}