#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rawSeq ;
struct TYPE_8__ {size_t size; size_t capacity; scalar_t__ pos; int /*<<< orphan*/ * seq; } ;
struct TYPE_6__ {int enableLdm; } ;
struct TYPE_7__ {TYPE_1__ ldmParams; } ;
struct TYPE_9__ {scalar_t__ stage; TYPE_3__ externSeqStore; TYPE_2__ appliedParams; } ;
typedef  TYPE_4__ ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTDcs_init ; 
 int /*<<< orphan*/  parameter_unsupported ; 
 int /*<<< orphan*/  stage_wrong ; 

size_t ZSTD_referenceExternalSequences(ZSTD_CCtx* cctx, rawSeq* seq, size_t nbSeq)
{
    RETURN_ERROR_IF(cctx->stage != ZSTDcs_init, stage_wrong);
    RETURN_ERROR_IF(cctx->appliedParams.ldmParams.enableLdm,
                    parameter_unsupported);
    cctx->externSeqStore.seq = seq;
    cctx->externSeqStore.size = nbSeq;
    cctx->externSeqStore.capacity = nbSeq;
    cctx->externSeqStore.pos = 0;
    return 0;
}