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
typedef  int /*<<< orphan*/  tOptions ;
struct TYPE_5__ {int /*<<< orphan*/  argEnum; } ;
struct TYPE_6__ {TYPE_1__ optArg; } ;
typedef  TYPE_2__ tOptDesc ;

/* Variables and functions */
 int /*<<< orphan*/ * OPTPROC_EMIT_LIMIT ; 
#define  ntpq_opt_strs 128 
 int /*<<< orphan*/  optionEnumerationVal (int /*<<< orphan*/ *,TYPE_2__*,char const* const*,int) ; 

__attribute__((used)) static void
doOptRefid(tOptions* pOptions, tOptDesc* pOptDesc)
{

/* extracted from optmain.tlib near line 945 */
    static char const * const names[2] = {
        ntpq_opt_strs+1972, ntpq_opt_strs+1041 };

    if (pOptions <= OPTPROC_EMIT_LIMIT) {
        (void) optionEnumerationVal(pOptions, pOptDesc, names, 2);
        return; /* protect AutoOpts client code from internal callbacks */
    }

    pOptDesc->optArg.argEnum =
        optionEnumerationVal(pOptions, pOptDesc, names, 2);
}