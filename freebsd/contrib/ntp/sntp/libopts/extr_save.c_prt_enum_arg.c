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
struct TYPE_6__ {uintptr_t argEnum; int /*<<< orphan*/  argString; } ;
struct TYPE_7__ {TYPE_1__ optArg; int /*<<< orphan*/  (* pOptProc ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  TYPE_2__ tOptDesc ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OPTPROC_RETURN_VALNAME ; 
 int /*<<< orphan*/  VOIDP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prt_entry (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
prt_enum_arg(FILE * fp, tOptDesc * od)
{
    uintptr_t val = od->optArg.argEnum;

    /*
     *  This is a magic incantation that will convert the
     *  bit flag values back into a string suitable for printing.
     */
    (*(od->pOptProc))(OPTPROC_RETURN_VALNAME, od);
    prt_entry(fp, od, VOIDP(od->optArg.argString));

    od->optArg.argEnum = val;
}