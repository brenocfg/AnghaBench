#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* vals; } ;
typedef  TYPE_1__ paramValues_t ;

/* Variables and functions */
 scalar_t__ ZSTD_btopt ; 
 scalar_t__ ZSTD_dfast ; 
 scalar_t__ ZSTD_fast ; 
 size_t clog_ind ; 
 size_t slog_ind ; 
 size_t strt_ind ; 
 size_t tlen_ind ; 

__attribute__((used)) static paramValues_t sanitizeParams(paramValues_t params)
{
    if (params.vals[strt_ind] == ZSTD_fast)
        params.vals[clog_ind] = 0, params.vals[slog_ind] = 0;
    if (params.vals[strt_ind] == ZSTD_dfast)
        params.vals[slog_ind] = 0;
    if ( (params.vals[strt_ind] < ZSTD_btopt) && (params.vals[strt_ind] != ZSTD_fast) )
        params.vals[tlen_ind] = 0;

    return params;
}