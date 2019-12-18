#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct TYPE_9__ {TYPE_1__ str; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ XmapVal ;
struct TYPE_10__ {char ch; int type; struct TYPE_10__* sibling; TYPE_2__ val; struct TYPE_10__* next; } ;
typedef  TYPE_3__ XmapNode ;
struct TYPE_11__ {char* buf; } ;
typedef  char Char ;
typedef  TYPE_4__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  F_SEND_EOF ; 
 int GetNextChar (char*) ; 
 int XK_CMD ; 
 int XK_STR ; 

__attribute__((used)) static int
TraverseMap(XmapNode *ptr, CStr *ch, XmapVal *val)
{
    Char    tch;

    if (ptr->ch == *(ch->buf)) {
	/* match found */
	if (ptr->next) {
	    /* Xkey not complete so get next char */
	    if (GetNextChar(&tch) != 1) {	/* if EOF or error */
		val->cmd = F_SEND_EOF;
		return XK_CMD;/* PWP: Pretend we just read an end-of-file */
	    }
	    *(ch->buf) = tch;
	    return (TraverseMap(ptr->next, ch, val));
	}
	else {
	    *val = ptr->val;
	    if (ptr->type != XK_CMD)
		*(ch->buf) = '\0';
	    return ptr->type;
	}
    }
    else {
	/* no match found here */
	if (ptr->sibling) {
	    /* try next sibling */
	    return (TraverseMap(ptr->sibling, ch, val));
	}
	else {
	    /* no next sibling -- mismatch */
	    val->str.buf = NULL;
	    val->str.len = 0;
	    return XK_STR;
	}
    }
}