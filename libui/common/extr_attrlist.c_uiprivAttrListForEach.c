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
struct TYPE_3__ {struct attr* first; } ;
typedef  TYPE_1__ uiprivAttrList ;
typedef  scalar_t__ uiForEach ;
typedef  scalar_t__ (* uiAttributedStringForEachAttributeFunc ) (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  uiAttributedString ;
struct attr {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  val; struct attr* next; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ uiForEachStop ; 

void uiprivAttrListForEach(const uiprivAttrList *alist, const uiAttributedString *s, uiAttributedStringForEachAttributeFunc f, void *data)
{
	struct attr *a;
	uiForEach ret;

	for (a = alist->first; a != NULL; a = a->next) {
		ret = (*f)(s, a->val, a->start, a->end, data);
		if (ret == uiForEachStop)
			// TODO for all: break or return?
			break;
	}
}