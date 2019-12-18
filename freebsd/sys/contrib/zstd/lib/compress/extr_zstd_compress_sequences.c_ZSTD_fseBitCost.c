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
struct TYPE_3__ {unsigned int stateLog; int /*<<< orphan*/  symbolTT; } ;
typedef  int /*<<< orphan*/  FSE_CTable ;
typedef  TYPE_1__ FSE_CState_t ;

/* Variables and functions */
 unsigned int FSE_bitCost (int /*<<< orphan*/ ,unsigned int const,unsigned int,unsigned int const) ; 
 int /*<<< orphan*/  FSE_initCState (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ,char*,unsigned int const,...) ; 
 unsigned int const ZSTD_getFSEMaxSymbolValue (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static size_t ZSTD_fseBitCost(
    FSE_CTable const* ctable,
    unsigned const* count,
    unsigned const max)
{
    unsigned const kAccuracyLog = 8;
    size_t cost = 0;
    unsigned s;
    FSE_CState_t cstate;
    FSE_initCState(&cstate, ctable);
    RETURN_ERROR_IF(ZSTD_getFSEMaxSymbolValue(ctable) < max, GENERIC,
                    "Repeat FSE_CTable has maxSymbolValue %u < %u",
                    ZSTD_getFSEMaxSymbolValue(ctable), max);
    for (s = 0; s <= max; ++s) {
        unsigned const tableLog = cstate.stateLog;
        unsigned const badCost = (tableLog + 1) << kAccuracyLog;
        unsigned const bitCost = FSE_bitCost(cstate.symbolTT, tableLog, s, kAccuracyLog);
        if (count[s] == 0)
            continue;
        RETURN_ERROR_IF(bitCost >= badCost, GENERIC,
                        "Repeat FSE_CTable has Prob[%u] == 0", s);
        cost += count[s] * bitCost;
    }
    return cost >> kAccuracyLog;
}