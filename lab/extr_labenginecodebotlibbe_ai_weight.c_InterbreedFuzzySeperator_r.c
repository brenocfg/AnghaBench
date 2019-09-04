#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; int weight; int maxweight; int minweight; struct TYPE_6__* next; struct TYPE_6__* child; } ;
typedef  TYPE_1__ fuzzyseperator_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 scalar_t__ WT_BALANCE ; 
 TYPE_2__ botimport ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 

int InterbreedFuzzySeperator_r(fuzzyseperator_t *fs1, fuzzyseperator_t *fs2,
								fuzzyseperator_t *fsout)
{
	if (fs1->child)
	{
		if (!fs2->child || !fsout->child)
		{
			botimport.Print(PRT_ERROR, "cannot interbreed weight configs, unequal child\n");
			return qfalse;
		} //end if
		if (!InterbreedFuzzySeperator_r(fs2->child, fs2->child, fsout->child))
		{
			return qfalse;
		} //end if
	} //end if
	else if (fs1->type == WT_BALANCE)
	{
		if (fs2->type != WT_BALANCE || fsout->type != WT_BALANCE)
		{
			botimport.Print(PRT_ERROR, "cannot interbreed weight configs, unequal balance\n");
			return qfalse;
		} //end if
		fsout->weight = (fs1->weight + fs2->weight) / 2;
		if (fsout->weight > fsout->maxweight) fsout->maxweight = fsout->weight;
		if (fsout->weight > fsout->minweight) fsout->minweight = fsout->weight;
	} //end else if
	if (fs1->next)
	{
		if (!fs2->next || !fsout->next)
		{
			botimport.Print(PRT_ERROR, "cannot interbreed weight configs, unequal next\n");
			return qfalse;
		} //end if
		if (!InterbreedFuzzySeperator_r(fs1->next, fs2->next, fsout->next))
		{
			return qfalse;
		} //end if
	} //end if
	return qtrue;
}