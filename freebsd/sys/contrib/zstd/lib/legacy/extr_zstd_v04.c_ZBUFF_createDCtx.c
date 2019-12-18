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
struct TYPE_4__ {int /*<<< orphan*/  stage; int /*<<< orphan*/  zc; } ;
typedef  TYPE_1__ ZBUFF_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZBUFFds_init ; 
 int /*<<< orphan*/  ZSTD_createDCtx () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ZBUFF_DCtx* ZBUFF_createDCtx(void)
{
    ZBUFF_DCtx* zbc = (ZBUFF_DCtx*)malloc(sizeof(ZBUFF_DCtx));
    if (zbc==NULL) return NULL;
    memset(zbc, 0, sizeof(*zbc));
    zbc->zc = ZSTD_createDCtx();
    zbc->stage = ZBUFFds_init;
    return zbc;
}