#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* buf; } ;
struct TYPE_7__ {TYPE_1__ str; } ;
struct TYPE_8__ {int type; TYPE_2__ val; struct TYPE_8__* sibling; struct TYPE_8__* next; } ;
typedef  TYPE_3__ XmapNode ;

/* Variables and functions */
#define  XK_CMD 131 
#define  XK_EXE 130 
#define  XK_NOD 129 
#define  XK_STR 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  xfree (TYPE_3__*) ; 

__attribute__((used)) static void
PutFreeNode(XmapNode *ptr)
{
    if (ptr == NULL)
	return;

    if (ptr->next != NULL) {
	PutFreeNode(ptr->next);
	ptr->next = NULL;
    }

    PutFreeNode(ptr->sibling);

    switch (ptr->type) {
    case XK_CMD:
    case XK_NOD:
	break;
    case XK_EXE:
    case XK_STR:
	xfree(ptr->val.str.buf);
	break;
    default:
	abort();
	break;
    }
    xfree(ptr);
}