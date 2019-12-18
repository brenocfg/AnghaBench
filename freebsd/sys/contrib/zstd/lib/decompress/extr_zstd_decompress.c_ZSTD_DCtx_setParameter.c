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
typedef  int /*<<< orphan*/  ZSTD_format_e ;
typedef  int ZSTD_dParameter ;
struct TYPE_3__ {scalar_t__ streamStage; size_t maxWindowSize; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ ZSTD_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_DBOUNDS (int const,int) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 int ZSTD_WINDOWLOG_LIMIT_DEFAULT ; 
#define  ZSTD_d_format 129 
#define  ZSTD_d_windowLogMax 128 
 int /*<<< orphan*/  parameter_unsupported ; 
 int /*<<< orphan*/  stage_wrong ; 
 scalar_t__ zdss_init ; 

size_t ZSTD_DCtx_setParameter(ZSTD_DCtx* dctx, ZSTD_dParameter dParam, int value)
{
    RETURN_ERROR_IF(dctx->streamStage != zdss_init, stage_wrong);
    switch(dParam) {
        case ZSTD_d_windowLogMax:
            if (value == 0) value = ZSTD_WINDOWLOG_LIMIT_DEFAULT;
            CHECK_DBOUNDS(ZSTD_d_windowLogMax, value);
            dctx->maxWindowSize = ((size_t)1) << value;
            return 0;
        case ZSTD_d_format:
            CHECK_DBOUNDS(ZSTD_d_format, value);
            dctx->format = (ZSTD_format_e)value;
            return 0;
        default:;
    }
    RETURN_ERROR(parameter_unsupported);
}