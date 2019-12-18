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
struct TYPE_3__ {int /*<<< orphan*/ * val; struct TYPE_3__* next; } ;
typedef  TYPE_1__ list ;
typedef  int /*<<< orphan*/  definition ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,char const*) ; 

definition *
findval(list *lst, const char *val, int (*cmp)(definition *, const char *))
{
	for (; lst != NULL; lst = lst->next) {
		if ((*cmp) (lst->val, val)) {
			return (lst->val);
		}
	}
	return (NULL);
}