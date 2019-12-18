#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ ZSTD_DStream ;
typedef  int /*<<< orphan*/  ZSTD_DDict ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_DCtx_refDDict (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZSTD_DCtx_reset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 
 size_t ZSTD_startingInputLength (int /*<<< orphan*/ ) ; 

size_t ZSTD_initDStream_usingDDict(ZSTD_DStream* dctx, const ZSTD_DDict* ddict)
{
    FORWARD_IF_ERROR( ZSTD_DCtx_reset(dctx, ZSTD_reset_session_only) );
    FORWARD_IF_ERROR( ZSTD_DCtx_refDDict(dctx, ddict) );
    return ZSTD_startingInputLength(dctx->format);
}