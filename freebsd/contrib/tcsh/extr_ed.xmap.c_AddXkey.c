#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cmd; } ;
typedef  TYPE_1__ XmapVal ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 scalar_t__ F_XKEY ; 
 int /*<<< orphan*/ * GetFreeNode (TYPE_2__*) ; 
 int /*<<< orphan*/  TryNode (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int) ; 
 int XK_CMD ; 
 int /*<<< orphan*/ * Xmap ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

void
AddXkey(const CStr *Xkey, XmapVal *val, int ntype)
{
    CStr cs;
    cs.buf = Xkey->buf;
    cs.len = Xkey->len;
    if (Xkey->len == 0) {
	xprintf("%s", CGETS(9, 1, "AddXkey: Null extended-key not allowed.\n"));
	return;
    }

    if (ntype == XK_CMD && val->cmd == F_XKEY) {
	xprintf("%s",
	    CGETS(9, 2, "AddXkey: sequence-lead-in command not allowed\n"));
	return;
    }

    if (Xmap == NULL)
	/* tree is initially empty.  Set up new node to match Xkey[0] */
	Xmap = GetFreeNode(&cs);	/* it is properly initialized */

    /* Now recurse through Xmap */
    (void) TryNode(Xmap, &cs, val, ntype);	
    return;
}