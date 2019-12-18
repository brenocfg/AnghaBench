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
typedef  TYPE_1__* z_streamp ;
typedef  int /*<<< orphan*/  ZWRAP_DCtx ;
struct TYPE_4__ {char* msg; scalar_t__ state; } ;

/* Variables and functions */
 int ZWRAPD_finishWithError (int /*<<< orphan*/ * const,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int Z_STREAM_ERROR ; 

__attribute__((used)) static int ZWRAPD_finishWithErrorMsg(z_streamp strm, char* message)
{
    ZWRAP_DCtx* const zwd = (ZWRAP_DCtx*) strm->state;
    strm->msg = message;
    if (zwd == NULL) return Z_STREAM_ERROR;

    return ZWRAPD_finishWithError(zwd, strm, 0);
}