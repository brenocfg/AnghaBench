#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ checksumFlag; } ;
struct TYPE_7__ {TYPE_1__ fParams; } ;
struct TYPE_6__ {scalar_t__ stage; int /*<<< orphan*/  xxhState; TYPE_3__ appliedParams; } ;
typedef  TYPE_2__ ZSTD_CCtx ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (size_t) ; 
 int /*<<< orphan*/  MEM_writeLE32 (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ XXH64_digest (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_blockHeaderSize ; 
 size_t ZSTD_writeFrameHeader (void*,size_t,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTDcs_created ; 
 scalar_t__ ZSTDcs_ending ; 
 scalar_t__ ZSTDcs_init ; 
 scalar_t__ ZSTDcs_ongoing ; 
 scalar_t__ bt_raw ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  stage_wrong ; 

__attribute__((used)) static size_t ZSTD_writeEpilogue(ZSTD_CCtx* cctx, void* dst, size_t dstCapacity)
{
    BYTE* const ostart = (BYTE*)dst;
    BYTE* op = ostart;
    size_t fhSize = 0;

    DEBUGLOG(4, "ZSTD_writeEpilogue");
    RETURN_ERROR_IF(cctx->stage == ZSTDcs_created, stage_wrong, "init missing");

    /* special case : empty frame */
    if (cctx->stage == ZSTDcs_init) {
        fhSize = ZSTD_writeFrameHeader(dst, dstCapacity, &cctx->appliedParams, 0, 0);
        FORWARD_IF_ERROR(fhSize);
        dstCapacity -= fhSize;
        op += fhSize;
        cctx->stage = ZSTDcs_ongoing;
    }

    if (cctx->stage != ZSTDcs_ending) {
        /* write one last empty block, make it the "last" block */
        U32 const cBlockHeader24 = 1 /* last block */ + (((U32)bt_raw)<<1) + 0;
        RETURN_ERROR_IF(dstCapacity<4, dstSize_tooSmall);
        MEM_writeLE32(op, cBlockHeader24);
        op += ZSTD_blockHeaderSize;
        dstCapacity -= ZSTD_blockHeaderSize;
    }

    if (cctx->appliedParams.fParams.checksumFlag) {
        U32 const checksum = (U32) XXH64_digest(&cctx->xxhState);
        RETURN_ERROR_IF(dstCapacity<4, dstSize_tooSmall);
        DEBUGLOG(4, "ZSTD_writeEpilogue: write checksum : %08X", (unsigned)checksum);
        MEM_writeLE32(op, checksum);
        op += 4;
    }

    cctx->stage = ZSTDcs_created;  /* return to "created but no init" status */
    return op-ostart;
}