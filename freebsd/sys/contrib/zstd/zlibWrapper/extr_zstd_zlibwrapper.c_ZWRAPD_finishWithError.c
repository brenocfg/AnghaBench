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
typedef  TYPE_1__* z_streamp ;
typedef  int /*<<< orphan*/  ZWRAP_DCtx ;
struct TYPE_3__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WRAPPERD (char*,int) ; 
 int /*<<< orphan*/  ZWRAP_freeDCtx (int /*<<< orphan*/ *) ; 
 int Z_STREAM_ERROR ; 

__attribute__((used)) static int ZWRAPD_finishWithError(ZWRAP_DCtx* zwd, z_streamp strm, int error)
{
    LOG_WRAPPERD("- ZWRAPD_finishWithError=%d\n", error);
    ZWRAP_freeDCtx(zwd);
    strm->state = NULL;
    return (error) ? error : Z_STREAM_ERROR;
}