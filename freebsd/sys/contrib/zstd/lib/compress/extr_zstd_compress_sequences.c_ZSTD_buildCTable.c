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
typedef  int symbolEncodingType_e ;
typedef  int /*<<< orphan*/  const U32 ;
typedef  int /*<<< orphan*/  const S16 ;
typedef  int /*<<< orphan*/  FSE_CTable ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 int /*<<< orphan*/  FORWARD_IF_ERROR (size_t const) ; 
 size_t const FSE_buildCTable_rle (int /*<<< orphan*/ *,size_t) ; 
 size_t const FSE_buildCTable_wksp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,void*,size_t) ; 
 size_t const FSE_normalizeCount (int /*<<< orphan*/  const*,int /*<<< orphan*/  const,unsigned int*,size_t,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const FSE_optimalTableLog (int /*<<< orphan*/  const,size_t,int /*<<< orphan*/  const) ; 
 size_t FSE_writeNCount (size_t*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  MaxSeq ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dstSize_tooSmall ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
#define  set_basic 131 
#define  set_compressed 130 
#define  set_repeat 129 
#define  set_rle 128 

size_t
ZSTD_buildCTable(void* dst, size_t dstCapacity,
                FSE_CTable* nextCTable, U32 FSELog, symbolEncodingType_e type,
                unsigned* count, U32 max,
                const BYTE* codeTable, size_t nbSeq,
                const S16* defaultNorm, U32 defaultNormLog, U32 defaultMax,
                const FSE_CTable* prevCTable, size_t prevCTableSize,
                void* entropyWorkspace, size_t entropyWorkspaceSize)
{
    BYTE* op = (BYTE*)dst;
    const BYTE* const oend = op + dstCapacity;
    DEBUGLOG(6, "ZSTD_buildCTable (dstCapacity=%u)", (unsigned)dstCapacity);

    switch (type) {
    case set_rle:
        FORWARD_IF_ERROR(FSE_buildCTable_rle(nextCTable, (BYTE)max));
        RETURN_ERROR_IF(dstCapacity==0, dstSize_tooSmall);
        *op = codeTable[0];
        return 1;
    case set_repeat:
        memcpy(nextCTable, prevCTable, prevCTableSize);
        return 0;
    case set_basic:
        FORWARD_IF_ERROR(FSE_buildCTable_wksp(nextCTable, defaultNorm, defaultMax, defaultNormLog, entropyWorkspace, entropyWorkspaceSize));  /* note : could be pre-calculated */
        return 0;
    case set_compressed: {
        S16 norm[MaxSeq + 1];
        size_t nbSeq_1 = nbSeq;
        const U32 tableLog = FSE_optimalTableLog(FSELog, nbSeq, max);
        if (count[codeTable[nbSeq-1]] > 1) {
            count[codeTable[nbSeq-1]]--;
            nbSeq_1--;
        }
        assert(nbSeq_1 > 1);
        FORWARD_IF_ERROR(FSE_normalizeCount(norm, tableLog, count, nbSeq_1, max));
        {   size_t const NCountSize = FSE_writeNCount(op, oend - op, norm, max, tableLog);   /* overflow protected */
            FORWARD_IF_ERROR(NCountSize);
            FORWARD_IF_ERROR(FSE_buildCTable_wksp(nextCTable, norm, max, tableLog, entropyWorkspace, entropyWorkspaceSize));
            return NCountSize;
        }
    }
    default: assert(0); RETURN_ERROR(GENERIC);
    }
}