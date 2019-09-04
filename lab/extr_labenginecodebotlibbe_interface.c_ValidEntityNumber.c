#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,char*,int,int) ;} ;
struct TYPE_3__ {int maxentities; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_2__ botimport ; 
 TYPE_1__ botlibglobals ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,char*,int,int) ; 

qboolean ValidEntityNumber(int num, char *str)
{
	if (num < 0 || num > botlibglobals.maxentities)
	{
		botimport.Print(PRT_ERROR, "%s: invalid entity number %d, [0, %d]\n",
										str, num, botlibglobals.maxentities);
		return qfalse;
	} //end if
	return qtrue;
}