#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_CStream ;
typedef  unsigned long long U64 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setPledgedSrcSize (int /*<<< orphan*/ *,unsigned long long const) ; 
 unsigned long long ZSTD_CONTENTSIZE_UNKNOWN ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 

size_t ZSTD_resetCStream(ZSTD_CStream* zcs, unsigned long long pss)
{
    /* temporary : 0 interpreted as "unknown" during transition period.
     * Users willing to specify "unknown" **must** use ZSTD_CONTENTSIZE_UNKNOWN.
     * 0 will be interpreted as "empty" in the future.
     */
    U64 const pledgedSrcSize = (pss==0) ? ZSTD_CONTENTSIZE_UNKNOWN : pss;
    DEBUGLOG(4, "ZSTD_resetCStream: pledgedSrcSize = %u", (unsigned)pledgedSrcSize);
    FORWARD_IF_ERROR( ZSTD_CCtx_reset(zcs, ZSTD_reset_session_only) );
    FORWARD_IF_ERROR( ZSTD_CCtx_setPledgedSrcSize(zcs, pledgedSrcSize) );
    return 0;
}