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
struct TYPE_4__ {int /*<<< orphan*/  customMem; struct TYPE_4__* version; int /*<<< orphan*/  zbd; } ;
typedef  TYPE_1__ ZWRAP_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_freeDStream (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZWRAP_freeDCtx(ZWRAP_DCtx* zwd)
{
    if (zwd==NULL) return 0;   /* support free on null */
    ZSTD_freeDStream(zwd->zbd);
    ZSTD_free(zwd->version, zwd->customMem);
    ZSTD_free(zwd, zwd->customMem);
    return 0;
}