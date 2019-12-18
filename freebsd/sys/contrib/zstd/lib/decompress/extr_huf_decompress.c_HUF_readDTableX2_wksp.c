#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* weight; void* symbol; } ;
typedef  TYPE_1__ sortedSymbol_t ;
typedef  int* rankValCol_t ;
typedef  int /*<<< orphan*/  dtd ;
typedef  int U32 ;
struct TYPE_7__ {int maxTableLog; int tableType; void* tableLog; } ;
typedef  int /*<<< orphan*/  HUF_DTable ;
typedef  int /*<<< orphan*/  HUF_DEltX2 ;
typedef  TYPE_2__ DTableDesc ;
typedef  void* BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_STATIC_ASSERT (int) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int HUF_ALIGN (int,int) ; 
 int HUF_SYMBOLVALUE_MAX ; 
 int HUF_TABLELOG_MAX ; 
 int /*<<< orphan*/  HUF_fillDTableX2 (int /*<<< orphan*/ * const,int const,TYPE_1__*,int,int*,int**,int,int) ; 
 TYPE_2__ HUF_getDTableDesc (int /*<<< orphan*/ *) ; 
 scalar_t__ HUF_isError (size_t) ; 
 size_t HUF_readStats (void**,int,int*,int*,int*,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tableLog_tooLarge ; 

size_t HUF_readDTableX2_wksp(HUF_DTable* DTable,
                       const void* src, size_t srcSize,
                             void* workSpace, size_t wkspSize)
{
    U32 tableLog, maxW, sizeOfSort, nbSymbols;
    DTableDesc dtd = HUF_getDTableDesc(DTable);
    U32 const maxTableLog = dtd.maxTableLog;
    size_t iSize;
    void* dtPtr = DTable+1;   /* force compiler to avoid strict-aliasing */
    HUF_DEltX2* const dt = (HUF_DEltX2*)dtPtr;
    U32 *rankStart;

    rankValCol_t* rankVal;
    U32* rankStats;
    U32* rankStart0;
    sortedSymbol_t* sortedSymbol;
    BYTE* weightList;
    size_t spaceUsed32 = 0;

    rankVal = (rankValCol_t *)((U32 *)workSpace + spaceUsed32);
    spaceUsed32 += (sizeof(rankValCol_t) * HUF_TABLELOG_MAX) >> 2;
    rankStats = (U32 *)workSpace + spaceUsed32;
    spaceUsed32 += HUF_TABLELOG_MAX + 1;
    rankStart0 = (U32 *)workSpace + spaceUsed32;
    spaceUsed32 += HUF_TABLELOG_MAX + 2;
    sortedSymbol = (sortedSymbol_t *)workSpace + (spaceUsed32 * sizeof(U32)) / sizeof(sortedSymbol_t);
    spaceUsed32 += HUF_ALIGN(sizeof(sortedSymbol_t) * (HUF_SYMBOLVALUE_MAX + 1), sizeof(U32)) >> 2;
    weightList = (BYTE *)((U32 *)workSpace + spaceUsed32);
    spaceUsed32 += HUF_ALIGN(HUF_SYMBOLVALUE_MAX + 1, sizeof(U32)) >> 2;

    if ((spaceUsed32 << 2) > wkspSize) return ERROR(tableLog_tooLarge);

    rankStart = rankStart0 + 1;
    memset(rankStats, 0, sizeof(U32) * (2 * HUF_TABLELOG_MAX + 2 + 1));

    DEBUG_STATIC_ASSERT(sizeof(HUF_DEltX2) == sizeof(HUF_DTable));   /* if compiler fails here, assertion is wrong */
    if (maxTableLog > HUF_TABLELOG_MAX) return ERROR(tableLog_tooLarge);
    /* memset(weightList, 0, sizeof(weightList)); */  /* is not necessary, even though some analyzer complain ... */

    iSize = HUF_readStats(weightList, HUF_SYMBOLVALUE_MAX + 1, rankStats, &nbSymbols, &tableLog, src, srcSize);
    if (HUF_isError(iSize)) return iSize;

    /* check result */
    if (tableLog > maxTableLog) return ERROR(tableLog_tooLarge);   /* DTable can't fit code depth */

    /* find maxWeight */
    for (maxW = tableLog; rankStats[maxW]==0; maxW--) {}  /* necessarily finds a solution before 0 */

    /* Get start index of each weight */
    {   U32 w, nextRankStart = 0;
        for (w=1; w<maxW+1; w++) {
            U32 current = nextRankStart;
            nextRankStart += rankStats[w];
            rankStart[w] = current;
        }
        rankStart[0] = nextRankStart;   /* put all 0w symbols at the end of sorted list*/
        sizeOfSort = nextRankStart;
    }

    /* sort symbols by weight */
    {   U32 s;
        for (s=0; s<nbSymbols; s++) {
            U32 const w = weightList[s];
            U32 const r = rankStart[w]++;
            sortedSymbol[r].symbol = (BYTE)s;
            sortedSymbol[r].weight = (BYTE)w;
        }
        rankStart[0] = 0;   /* forget 0w symbols; this is beginning of weight(1) */
    }

    /* Build rankVal */
    {   U32* const rankVal0 = rankVal[0];
        {   int const rescale = (maxTableLog-tableLog) - 1;   /* tableLog <= maxTableLog */
            U32 nextRankVal = 0;
            U32 w;
            for (w=1; w<maxW+1; w++) {
                U32 current = nextRankVal;
                nextRankVal += rankStats[w] << (w+rescale);
                rankVal0[w] = current;
        }   }
        {   U32 const minBits = tableLog+1 - maxW;
            U32 consumed;
            for (consumed = minBits; consumed < maxTableLog - minBits + 1; consumed++) {
                U32* const rankValPtr = rankVal[consumed];
                U32 w;
                for (w = 1; w < maxW+1; w++) {
                    rankValPtr[w] = rankVal0[w] >> consumed;
    }   }   }   }

    HUF_fillDTableX2(dt, maxTableLog,
                   sortedSymbol, sizeOfSort,
                   rankStart0, rankVal, maxW,
                   tableLog+1);

    dtd.tableLog = (BYTE)maxTableLog;
    dtd.tableType = 1;
    memcpy(DTable, &dtd, sizeof(dtd));
    return iSize;
}