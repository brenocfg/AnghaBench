#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* originalOptArgArray; } ;
typedef  TYPE_3__ tOptions ;
struct TYPE_10__ {char const* argString; } ;
struct TYPE_12__ {char const* optCookie; size_t optIndex; TYPE_2__ optArg; } ;
typedef  TYPE_4__ tOptDesc ;
struct TYPE_9__ {char* argString; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ HAS_originalOptArgArray (TYPE_3__*) ; 
 int /*<<< orphan*/  prt_entry (int /*<<< orphan*/ *,TYPE_4__*,char const*) ; 

__attribute__((used)) static void
prt_file_arg(FILE * fp, tOptDesc * od, tOptions * opts)
{
    /*
     *  If the cookie is not NULL, then it has the file name, period.
     *  Otherwise, if we have a non-NULL string argument, then....
     */
    if (od->optCookie != NULL)
        prt_entry(fp, od, od->optCookie);

    else if (HAS_originalOptArgArray(opts)) {
        char const * orig =
            opts->originalOptArgArray[od->optIndex].argString;

        if (od->optArg.argString == orig)
            return;

        prt_entry(fp, od, od->optArg.argString);
    }
}