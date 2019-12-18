#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  str; struct TYPE_5__* next; } ;
typedef  TYPE_1__ strlst_t ;

/* Variables and functions */
 scalar_t__ in_list (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
subtract_strlst(strlst_t **lista, strlst_t **listb)
{
	int subtract_count = 0;
	strlst_t *p1;
	for (p1 = *listb; p1 != NULL; p1 = p1->next)
		if ( in_list(lista, p1->str) ) {
			warnx("Will compile library `%s' dynamically", p1->str);
			strcat(p1->str, "");
			subtract_count++;
		}
	return subtract_count;
}