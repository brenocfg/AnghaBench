#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tRowcnt ;
struct TYPE_9__ {int /*<<< orphan*/  db; int /*<<< orphan*/  zDatabase; } ;
typedef  TYPE_1__ analysisInfo ;
struct TYPE_10__ {int /*<<< orphan*/  tabFlags; int /*<<< orphan*/  szTabRow; int /*<<< orphan*/  nRowLogEst; } ;
typedef  TYPE_2__ Table ;
struct TYPE_11__ {int nKeyCol; int hasStat1; scalar_t__ pPartIdxWhere; int /*<<< orphan*/  szIdxRow; TYPE_2__* pTable; int /*<<< orphan*/ * aiRowLogEst; scalar_t__ bUnordered; int /*<<< orphan*/ * aiRowEst; } ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  TF_HasStat1 ; 
 int /*<<< orphan*/  UNUSED_PARAMETER2 (char**,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  decodeIntArray (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* sqlite3FindIndex (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* sqlite3FindTable (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3MallocZero (int) ; 
 int /*<<< orphan*/  sqlite3OomFault (int /*<<< orphan*/ ) ; 
 TYPE_3__* sqlite3PrimaryKeyIndex (TYPE_2__*) ; 
 scalar_t__ sqlite3_stricmp (char*,char*) ; 

__attribute__((used)) static int analysisLoader(void *pData, int argc, char **argv, char **NotUsed){
  analysisInfo *pInfo = (analysisInfo*)pData;
  Index *pIndex;
  Table *pTable;
  const char *z;

  assert( argc==3 );
  UNUSED_PARAMETER2(NotUsed, argc);

  if( argv==0 || argv[0]==0 || argv[2]==0 ){
    return 0;
  }
  pTable = sqlite3FindTable(pInfo->db, argv[0], pInfo->zDatabase);
  if( pTable==0 ){
    return 0;
  }
  if( argv[1]==0 ){
    pIndex = 0;
  }else if( sqlite3_stricmp(argv[0],argv[1])==0 ){
    pIndex = sqlite3PrimaryKeyIndex(pTable);
  }else{
    pIndex = sqlite3FindIndex(pInfo->db, argv[1], pInfo->zDatabase);
  }
  z = argv[2];

  if( pIndex ){
    tRowcnt *aiRowEst = 0;
    int nCol = pIndex->nKeyCol+1;
#ifdef SQLITE_ENABLE_STAT4
    /* Index.aiRowEst may already be set here if there are duplicate 
    ** sqlite_stat1 entries for this index. In that case just clobber
    ** the old data with the new instead of allocating a new array.  */
    if( pIndex->aiRowEst==0 ){
      pIndex->aiRowEst = (tRowcnt*)sqlite3MallocZero(sizeof(tRowcnt) * nCol);
      if( pIndex->aiRowEst==0 ) sqlite3OomFault(pInfo->db);
    }
    aiRowEst = pIndex->aiRowEst;
#endif
    pIndex->bUnordered = 0;
    decodeIntArray((char*)z, nCol, aiRowEst, pIndex->aiRowLogEst, pIndex);
    pIndex->hasStat1 = 1;
    if( pIndex->pPartIdxWhere==0 ){
      pTable->nRowLogEst = pIndex->aiRowLogEst[0];
      pTable->tabFlags |= TF_HasStat1;
    }
  }else{
    Index fakeIdx;
    fakeIdx.szIdxRow = pTable->szTabRow;
#ifdef SQLITE_ENABLE_COSTMULT
    fakeIdx.pTable = pTable;
#endif
    decodeIntArray((char*)z, 1, 0, &pTable->nRowLogEst, &fakeIdx);
    pTable->szTabRow = fakeIdx.szIdxRow;
    pTable->tabFlags |= TF_HasStat1;
  }

  return 0;
}