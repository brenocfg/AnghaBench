#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  window; } ;
struct TYPE_8__ {TYPE_2__ matchState; TYPE_1__* prevCBlock; } ;
struct TYPE_9__ {TYPE_3__ blockState; } ;
typedef  TYPE_4__ ZSTD_CCtx ;
struct TYPE_6__ {scalar_t__* rep; } ;

/* Variables and functions */
 int ZSTD_REP_NUM ; 
 int /*<<< orphan*/  ZSTD_window_hasExtDict (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

void ZSTD_invalidateRepCodes(ZSTD_CCtx* cctx) {
    int i;
    for (i=0; i<ZSTD_REP_NUM; i++) cctx->blockState.prevCBlock->rep[i] = 0;
    assert(!ZSTD_window_hasExtDict(cctx->blockState.matchState.window));
}