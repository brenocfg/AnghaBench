#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct attr* first; } ;
typedef  TYPE_1__ uiprivAttrList ;
struct attr {int dummy; } ;

/* Variables and functions */
 struct attr* attrDeleteRange (TYPE_1__*,struct attr*,size_t,size_t) ; 

void uiprivAttrListRemoveCharacters(uiprivAttrList *alist, size_t start, size_t end)
{
	struct attr *a;

	a = alist->first;
	while (a != NULL)
		a = attrDeleteRange(alist, a, start, end);
}