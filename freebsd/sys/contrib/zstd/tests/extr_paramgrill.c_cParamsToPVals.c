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
typedef  size_t varInds_t ;
struct TYPE_5__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ paramValues_t ;
struct TYPE_6__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  targetLength; int /*<<< orphan*/  minMatch; int /*<<< orphan*/  searchLog; int /*<<< orphan*/  hashLog; int /*<<< orphan*/  chainLog; int /*<<< orphan*/  windowLog; } ;
typedef  TYPE_2__ ZSTD_compressionParameters ;

/* Variables and functions */
 size_t NUM_PARAMS ; 
 size_t clog_ind ; 
 size_t hlog_ind ; 
 int /*<<< orphan*/ * mintable ; 
 size_t mml_ind ; 
 size_t slog_ind ; 
 size_t strt_ind ; 
 size_t tlen_ind ; 
 size_t wlog_ind ; 

__attribute__((used)) static paramValues_t cParamsToPVals(ZSTD_compressionParameters c)
{
    paramValues_t p;
    varInds_t i;
    p.vals[wlog_ind] = c.windowLog;
    p.vals[clog_ind] = c.chainLog;
    p.vals[hlog_ind] = c.hashLog;
    p.vals[slog_ind] = c.searchLog;
    p.vals[mml_ind]  = c.minMatch;
    p.vals[tlen_ind] = c.targetLength;
    p.vals[strt_ind] = c.strategy;

    /* set all other params to their minimum value */
    for (i = strt_ind + 1; i < NUM_PARAMS; i++) {
        p.vals[i] = mintable[i];
    }
    return p;
}