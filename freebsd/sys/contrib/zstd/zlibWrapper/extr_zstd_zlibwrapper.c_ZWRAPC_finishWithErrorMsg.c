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
typedef  int /*<<< orphan*/  ZWRAP_CCtx ;
struct TYPE_4__ {char* msg; scalar_t__ state; } ;

/* Variables and functions */
 int ZWRAPC_finishWithError (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int Z_STREAM_ERROR ; 

__attribute__((used)) static int ZWRAPC_finishWithErrorMsg(z_streamp strm, char* message)
{
    ZWRAP_CCtx* zwc = (ZWRAP_CCtx*) strm->state;
    strm->msg = message;
    if (zwc == NULL) return Z_STREAM_ERROR;

    return ZWRAPC_finishWithError(zwc, strm, 0);
}