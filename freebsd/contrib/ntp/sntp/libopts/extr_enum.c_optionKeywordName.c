#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int argEnum; char const* argString; } ;
struct TYPE_6__ {TYPE_1__ optArg; int /*<<< orphan*/  (* pOptProc ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/  OPTPROC_RETURN_VALNAME ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

char const *
optionKeywordName(tOptDesc * pOD, unsigned int enum_val)
{
    tOptDesc od = { 0 };
    od.optArg.argEnum = enum_val;

    (*(pOD->pOptProc))(OPTPROC_RETURN_VALNAME, &od );
    return od.optArg.argString;
}