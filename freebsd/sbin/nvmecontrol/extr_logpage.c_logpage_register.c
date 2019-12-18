#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct logpage_function {int dummy; } ;

/* Variables and functions */
 struct logpage_function* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_AFTER (struct logpage_function*,struct logpage_function*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct logpage_function*,int /*<<< orphan*/ ) ; 
 struct logpage_function* SLIST_NEXT (struct logpage_function*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ logpage_compare (struct logpage_function*,struct logpage_function*) ; 
 int /*<<< orphan*/  logpages ; 

void
logpage_register(struct logpage_function *p)
{
	struct logpage_function *l, *a;

	a = NULL;
	l = SLIST_FIRST(&logpages);
	while (l != NULL) {
		if (logpage_compare(l, p) > 0)
			break;
		a = l;
		l = SLIST_NEXT(l, link);
	}
	if (a == NULL)
		SLIST_INSERT_HEAD(&logpages, p, link);
	else
		SLIST_INSERT_AFTER(a, p, link);
}