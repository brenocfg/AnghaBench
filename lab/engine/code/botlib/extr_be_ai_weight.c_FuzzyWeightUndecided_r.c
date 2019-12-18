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
struct TYPE_4__ {size_t index; int value; float minweight; float maxweight; float weight; struct TYPE_4__* next; struct TYPE_4__* child; } ;
typedef  TYPE_1__ fuzzyseperator_t ;

/* Variables and functions */
 float FuzzyWeight_r (int*,TYPE_1__*) ; 
 int MAX_INVENTORYVALUE ; 
 float random () ; 

float FuzzyWeightUndecided_r(int *inventory, fuzzyseperator_t *fs)
{
	float scale, w1, w2;

	if (inventory[fs->index] < fs->value)
	{
		if (fs->child) return FuzzyWeightUndecided_r(inventory, fs->child);
		else return fs->minweight + random() * (fs->maxweight - fs->minweight);
	} //end if
	else if (fs->next)
	{
		if (inventory[fs->index] < fs->next->value)
		{
			//first weight
			if (fs->child) w1 = FuzzyWeightUndecided_r(inventory, fs->child);
			else w1 = fs->minweight + random() * (fs->maxweight - fs->minweight);
			//second weight
			if (fs->next->child) w2 = FuzzyWeight_r(inventory, fs->next->child);
			else w2 = fs->next->minweight + random() * (fs->next->maxweight - fs->next->minweight);
			//the scale factor
			if(fs->next->value == MAX_INVENTORYVALUE) // is fs->next the default case?
        		return w2;      // can't interpolate, return default weight
			else
				scale = (float) (inventory[fs->index] - fs->value) / (fs->next->value - fs->value);
			//scale between the two weights
			return (1 - scale) * w1 + scale * w2;
		} //end if
		return FuzzyWeightUndecided_r(inventory, fs->next);
	} //end else if
	return fs->weight;
}