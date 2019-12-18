#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  targetLength; int /*<<< orphan*/  strategy; } ;
struct TYPE_5__ {int literalCompressionMode; TYPE_1__ cParams; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_fast ; 
#define  ZSTD_lcm_auto 130 
#define  ZSTD_lcm_huffman 129 
#define  ZSTD_lcm_uncompressed 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ZSTD_disableLiteralsCompression(const ZSTD_CCtx_params* cctxParams)
{
    switch (cctxParams->literalCompressionMode) {
    case ZSTD_lcm_huffman:
        return 0;
    case ZSTD_lcm_uncompressed:
        return 1;
    default:
        assert(0 /* impossible: pre-validated */);
        /* fall-through */
    case ZSTD_lcm_auto:
        return (cctxParams->cParams.strategy == ZSTD_fast) && (cctxParams->cParams.targetLength > 0);
    }
}