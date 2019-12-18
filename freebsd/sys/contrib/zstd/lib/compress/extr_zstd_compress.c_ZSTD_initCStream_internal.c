#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cParams; } ;
struct TYPE_9__ {TYPE_2__ requestedParams; } ;
typedef  TYPE_1__ ZSTD_CStream ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;
typedef  TYPE_2__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_loadDictionary (TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_CCtx_refCDict (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ZSTD_CCtx_reset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setPledgedSrcSize (TYPE_1__*,unsigned long long) ; 
 int /*<<< orphan*/  ZSTD_checkCParams (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_isError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 
 int /*<<< orphan*/  assert (int) ; 

size_t ZSTD_initCStream_internal(ZSTD_CStream* zcs,
                    const void* dict, size_t dictSize, const ZSTD_CDict* cdict,
                    const ZSTD_CCtx_params* params,
                    unsigned long long pledgedSrcSize)
{
    DEBUGLOG(4, "ZSTD_initCStream_internal");
    FORWARD_IF_ERROR( ZSTD_CCtx_reset(zcs, ZSTD_reset_session_only) );
    FORWARD_IF_ERROR( ZSTD_CCtx_setPledgedSrcSize(zcs, pledgedSrcSize) );
    assert(!ZSTD_isError(ZSTD_checkCParams(params->cParams)));
    zcs->requestedParams = *params;
    assert(!((dict) && (cdict)));  /* either dict or cdict, not both */
    if (dict) {
        FORWARD_IF_ERROR( ZSTD_CCtx_loadDictionary(zcs, dict, dictSize) );
    } else {
        /* Dictionary is cleared if !cdict */
        FORWARD_IF_ERROR( ZSTD_CCtx_refCDict(zcs, cdict) );
    }
    return 0;
}