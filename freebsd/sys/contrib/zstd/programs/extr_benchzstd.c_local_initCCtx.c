#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  adv; int /*<<< orphan*/  comprParams; int /*<<< orphan*/  cLevel; int /*<<< orphan*/  dictBufferSize; int /*<<< orphan*/  dictBuffer; int /*<<< orphan*/  cctx; } ;
typedef  TYPE_1__ BMK_initCCtxArgs ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_initCCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t local_initCCtx(void* payload) {
    BMK_initCCtxArgs* ag = (BMK_initCCtxArgs*)payload;
    BMK_initCCtx(ag->cctx, ag->dictBuffer, ag->dictBufferSize, ag->cLevel, ag->comprParams, ag->adv);
    return 0;
}