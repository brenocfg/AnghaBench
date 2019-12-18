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
struct TYPE_6__ {scalar_t__ ch; struct TYPE_6__* sibling; struct TYPE_6__* next; } ;
typedef  TYPE_1__ XmapNode ;
struct TYPE_7__ {scalar_t__* buf; scalar_t__ len; } ;
typedef  TYPE_2__ CStr ;

/* Variables and functions */
 int /*<<< orphan*/  PutFreeNode (TYPE_1__*) ; 

__attribute__((used)) static int
TryDeleteNode(XmapNode **inptr, CStr *str)
{
    XmapNode *ptr;

    ptr = *inptr;
    /*
     * Find a node that matches *string or allocate a new one
     */
    if (ptr->ch != *(str->buf)) {
	XmapNode *xm;

	for (xm = ptr; xm->sibling != NULL; xm = xm->sibling)
	    if (xm->sibling->ch == *(str->buf))
		break;
	if (xm->sibling == NULL)
	    return (0);
	inptr = &xm->sibling;
	ptr = xm->sibling;
    }

    str->buf++;
    str->len--;

    if (str->len == 0) {
	/* we're there */
	*inptr = ptr->sibling;
	ptr->sibling = NULL;
	PutFreeNode(ptr);
	return (1);
    }
    else if (ptr->next != NULL && TryDeleteNode(&ptr->next, str) == 1) {
	if (ptr->next != NULL)
	    return (0);
	*inptr = ptr->sibling;
	ptr->sibling = NULL;
	PutFreeNode(ptr);
	return (1);
    }
    else {
	return (0);
    }
}