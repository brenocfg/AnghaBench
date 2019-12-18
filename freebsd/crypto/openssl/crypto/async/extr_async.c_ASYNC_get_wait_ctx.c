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
struct TYPE_3__ {int /*<<< orphan*/ * waitctx; } ;
typedef  int /*<<< orphan*/  ASYNC_WAIT_CTX ;
typedef  TYPE_1__ ASYNC_JOB ;

/* Variables and functions */

ASYNC_WAIT_CTX *ASYNC_get_wait_ctx(ASYNC_JOB *job)
{
    return job->waitctx;
}