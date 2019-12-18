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
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/ * buf; } ;
struct TYPE_8__ {TYPE_2__ str; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sibling; int /*<<< orphan*/ * next; TYPE_1__ val; int /*<<< orphan*/  type; int /*<<< orphan*/  ch; } ;
typedef  TYPE_3__ XmapNode ;
struct TYPE_11__ {int /*<<< orphan*/ * buf; } ;
typedef  TYPE_4__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  XK_NOD ; 
 TYPE_3__* xmalloc (int) ; 

__attribute__((used)) static XmapNode *
GetFreeNode(CStr *ch)
{
    XmapNode *ptr;

    ptr = xmalloc(sizeof(XmapNode));
    ptr->ch = ch->buf[0];
    ptr->type = XK_NOD;
    ptr->val.str.buf = NULL;
    ptr->val.str.len = 0;
    ptr->next = NULL;
    ptr->sibling = NULL;
    return (ptr);
}