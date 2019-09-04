#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* weights; } ;
typedef  TYPE_2__ weightconfig_t ;
struct TYPE_7__ {size_t index; int value; float weight; struct TYPE_7__* next; struct TYPE_7__* child; } ;
typedef  TYPE_3__ fuzzyseperator_t ;
struct TYPE_5__ {TYPE_3__* firstseperator; } ;

/* Variables and functions */

float FuzzyWeight(int *inventory, weightconfig_t *wc, int weightnum)
{
#ifdef EVALUATERECURSIVELY
	return FuzzyWeight_r(inventory, wc->weights[weightnum].firstseperator);
#else
	fuzzyseperator_t *s;

	s = wc->weights[weightnum].firstseperator;
	if (!s) return 0;
	while(1)
	{
		if (inventory[s->index] < s->value)
		{
			if (s->child) s = s->child;
			else return s->weight;
		} //end if
		else
		{
			if (s->next) s = s->next;
			else return s->weight;
		} //end else
	} //end if
	return 0;
#endif
}