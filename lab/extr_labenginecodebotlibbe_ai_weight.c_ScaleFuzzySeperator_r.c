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
struct TYPE_3__ {scalar_t__ type; float weight; float maxweight; float minweight; struct TYPE_3__* next; struct TYPE_3__* child; } ;
typedef  TYPE_1__ fuzzyseperator_t ;

/* Variables and functions */
 scalar_t__ WT_BALANCE ; 

void ScaleFuzzySeperator_r(fuzzyseperator_t *fs, float scale)
{
	if (fs->child)
	{
		ScaleFuzzySeperator_r(fs->child, scale);
	} //end if
	else if (fs->type == WT_BALANCE)
	{
		//
		fs->weight = (float) (fs->maxweight + fs->minweight) * scale;
		//get the weight between bounds
		if (fs->weight < fs->minweight) fs->weight = fs->minweight;
		else if (fs->weight > fs->maxweight) fs->weight = fs->maxweight;
	} //end else if
	if (fs->next) ScaleFuzzySeperator_r(fs->next, scale);
}