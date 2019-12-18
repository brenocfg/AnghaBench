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
struct TYPE_4__ {struct TYPE_4__* outBuff; struct TYPE_4__* inBuff; int /*<<< orphan*/  zc; } ;
typedef  TYPE_1__ ZBUFF_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static size_t ZBUFF_freeDCtx(ZBUFF_DCtx* zbc)
{
    if (zbc==NULL) return 0;   /* support free on null */
    ZSTD_freeDCtx(zbc->zc);
    free(zbc->inBuff);
    free(zbc->outBuff);
    free(zbc);
    return 0;
}