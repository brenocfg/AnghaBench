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
typedef  int U32 ;
typedef  int /*<<< orphan*/  const S16 ;
typedef  int /*<<< orphan*/  FSEv07_DTable ;
typedef  int BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
#define  FSEv07_ENCODING_DYNAMIC 131 
#define  FSEv07_ENCODING_RAW 130 
#define  FSEv07_ENCODING_RLE 129 
#define  FSEv07_ENCODING_STATIC 128 
 int /*<<< orphan*/  FSEv07_buildDTable (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  FSEv07_buildDTable_rle (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  FSEv07_isError (size_t const) ; 
 size_t FSEv07_readNCount (int /*<<< orphan*/  const*,int*,int*,void const*,size_t) ; 
 int /*<<< orphan*/  MaxSeq ; 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv07_buildSeqTable(FSEv07_DTable* DTable, U32 type, U32 max, U32 maxLog,
                                 const void* src, size_t srcSize,
                                 const S16* defaultNorm, U32 defaultLog, U32 flagRepeatTable)
{
    switch(type)
    {
    case FSEv07_ENCODING_RLE :
        if (!srcSize) return ERROR(srcSize_wrong);
        if ( (*(const BYTE*)src) > max) return ERROR(corruption_detected);
        FSEv07_buildDTable_rle(DTable, *(const BYTE*)src);   /* if *src > max, data is corrupted */
        return 1;
    case FSEv07_ENCODING_RAW :
        FSEv07_buildDTable(DTable, defaultNorm, max, defaultLog);
        return 0;
    case FSEv07_ENCODING_STATIC:
        if (!flagRepeatTable) return ERROR(corruption_detected);
        return 0;
    default :   /* impossible */
    case FSEv07_ENCODING_DYNAMIC :
        {   U32 tableLog;
            S16 norm[MaxSeq+1];
            size_t const headerSize = FSEv07_readNCount(norm, &max, &tableLog, src, srcSize);
            if (FSEv07_isError(headerSize)) return ERROR(corruption_detected);
            if (tableLog > maxLog) return ERROR(corruption_detected);
            FSEv07_buildDTable(DTable, norm, max, tableLog);
            return headerSize;
    }   }
}