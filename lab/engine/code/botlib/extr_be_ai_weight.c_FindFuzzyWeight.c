#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numweights; TYPE_1__* weights; } ;
typedef  TYPE_2__ weightconfig_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int FindFuzzyWeight(weightconfig_t *wc, char *name)
{
	int i;

	for (i = 0; i < wc->numweights; i++)
	{
		if (!strcmp(wc->weights[i].name, name))
		{
			return i;
		} //end if
	} //end if
	return -1;
}