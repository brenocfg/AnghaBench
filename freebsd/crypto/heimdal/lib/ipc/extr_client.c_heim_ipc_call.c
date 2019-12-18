#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* heim_ipc ;
typedef  int /*<<< orphan*/  heim_idata ;
typedef  int /*<<< orphan*/ * heim_icred ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* ipc ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
heim_ipc_call(heim_ipc ctx, const heim_idata *snd, heim_idata *rcv,
	      heim_icred *cred)
{
    if (cred)
	*cred = NULL;
    return (ctx->ops->ipc)(ctx->ctx, snd, rcv, cred);
}