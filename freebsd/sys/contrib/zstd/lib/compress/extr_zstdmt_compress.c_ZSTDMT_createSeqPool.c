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
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTDMT_seqPool ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTDMT_createBufferPool (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_setNbSeq (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ZSTDMT_seqPool* ZSTDMT_createSeqPool(unsigned nbWorkers, ZSTD_customMem cMem)
{
    ZSTDMT_seqPool* const seqPool = ZSTDMT_createBufferPool(nbWorkers, cMem);
    if (seqPool == NULL) return NULL;
    ZSTDMT_setNbSeq(seqPool, 0);
    return seqPool;
}