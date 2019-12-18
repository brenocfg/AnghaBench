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
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ strlst_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  out_of_memory () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

void
add_string(strlst_t **listp, char *str)
{
	strlst_t *p1, *p2;

	/* add to end, but be smart about dups */

	for (p1 = NULL, p2 = *listp; p2 != NULL; p1 = p2, p2 = p2->next)
		if (!strcmp(p2->str, str))
			return;

	p2 = malloc(sizeof(strlst_t));
	if (p2) {
		p2->next = NULL;
		p2->str = strdup(str);
    	}
	if (!p2 || !p2->str)
		out_of_memory();

	if (p1 == NULL)
		*listp = p2;
	else
		p1->next = p2;
}