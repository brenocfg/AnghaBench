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
struct attr_counter {struct attr_counter* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct attr_counter*) ; 

__attribute__((used)) static void
attr_counter_free(struct attr_counter **top)
{
	struct attr_counter *ac, *tac;

	if (*top == NULL)
		return;
	ac = *top;
        while (ac != NULL) {
		tac = ac->next;
		free(ac);
		ac = tac;
	}
	*top = NULL;
}