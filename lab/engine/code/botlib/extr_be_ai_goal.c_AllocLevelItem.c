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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ levelitem_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PRT_FATAL ; 
 TYPE_3__ botimport ; 
 TYPE_1__* freelevelitems ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

levelitem_t *AllocLevelItem(void)
{
	levelitem_t *li;

	li = freelevelitems;
	if (!li)
	{
		botimport.Print(PRT_FATAL, "out of level items\n");
		return NULL;
	} //end if
	//
	freelevelitems = freelevelitems->next;
	Com_Memset(li, 0, sizeof(levelitem_t));
	return li;
}