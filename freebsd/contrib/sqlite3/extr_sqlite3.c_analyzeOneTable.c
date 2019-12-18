#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_36__ {scalar_t__ xPreUpdateCallback; TYPE_1__* aDb; } ;
typedef  TYPE_3__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_37__ {char* zName; int nCol; int iPKey; TYPE_2__* aCol; TYPE_6__* pIndex; int /*<<< orphan*/  tnum; int /*<<< orphan*/  pSchema; } ;
typedef  TYPE_4__ Table ;
struct TYPE_39__ {scalar_t__ pPartIdxWhere; int nKeyCol; int nColumn; char* zName; int tnum; size_t* aiColumn; int /*<<< orphan*/  pTable; int /*<<< orphan*/ * azColl; int /*<<< orphan*/  pSchema; scalar_t__ uniqNotNull; struct TYPE_39__* pNext; } ;
struct TYPE_38__ {void* nMem; void* nTab; int /*<<< orphan*/ * pVdbe; TYPE_3__* db; } ;
struct TYPE_35__ {int /*<<< orphan*/  zName; } ;
struct TYPE_34__ {int /*<<< orphan*/  zDbSName; } ;
typedef  TYPE_5__ Parse ;
typedef  TYPE_6__ Index ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_4__*) ; 
 scalar_t__ IsPrimaryKeyIndex (TYPE_6__*) ; 
 scalar_t__ IsStat4 ; 
 scalar_t__ IsUniqueIndex (TYPE_6__*) ; 
 void* MAX (void*,int) ; 
 scalar_t__ NEVER (int) ; 
 scalar_t__ OPFLAG_APPEND ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Count ; 
 int /*<<< orphan*/  OP_Function0 ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IdxRowid ; 
 int /*<<< orphan*/  OP_IfNot ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_Ne ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_Noop ; 
 int OP_NotExists ; 
 int OP_NotFound ; 
 int /*<<< orphan*/  OP_NotNull ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_OpenRead ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  P4_COLLSEQ ; 
 int /*<<< orphan*/  P4_DYNBLOB ; 
 int /*<<< orphan*/  P4_FUNCDEF ; 
 int /*<<< orphan*/  P4_TABLE ; 
 char SQLITE_AFF_TEXT ; 
 int /*<<< orphan*/  SQLITE_ANALYZE ; 
 scalar_t__ SQLITE_NULLEQ ; 
 int /*<<< orphan*/  STAT_GET_NDLT ; 
 int /*<<< orphan*/  STAT_GET_NEQ ; 
 int /*<<< orphan*/  STAT_GET_NLT ; 
 int /*<<< orphan*/  STAT_GET_ROWID ; 
 int /*<<< orphan*/  STAT_GET_STAT1 ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  callStatGet (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3BtreeHoldsAllMutexes (TYPE_3__*) ; 
 int sqlite3ColumnOfIndex (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_3__*,int*) ; 
 int* sqlite3DbMallocRawNN (TYPE_3__*,int) ; 
 scalar_t__ sqlite3DbMallocZero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeLoadIndexColumn (TYPE_5__*,TYPE_6__*,int,int,int) ; 
 int sqlite3GetTempRange (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_5__*) ; 
 scalar_t__ sqlite3LocateCollSeq (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OpenTable (TYPE_5__*,int,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* sqlite3PrimaryKeyIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempRange (TYPE_5__*,int,int) ; 
 int sqlite3SchemaMutexHeld (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int sqlite3SchemaToIndex (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3TableLock (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP4 (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,scalar_t__) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeLoadString (int /*<<< orphan*/ *,int,char const*) ; 
 int sqlite3VdbeMakeLabel (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeSetP4KeyInfo (TYPE_5__*,TYPE_6__*) ; 
 scalar_t__ sqlite3_strlike (char*,char*,char) ; 
 int /*<<< orphan*/  statInitFuncdef ; 
 int /*<<< orphan*/  statPushFuncdef ; 

__attribute__((used)) static void analyzeOneTable(
  Parse *pParse,   /* Parser context */
  Table *pTab,     /* Table whose indices are to be analyzed */
  Index *pOnlyIdx, /* If not NULL, only analyze this one index */
  int iStatCur,    /* Index of VdbeCursor that writes the sqlite_stat1 table */
  int iMem,        /* Available memory locations begin here */
  int iTab         /* Next available cursor */
){
  sqlite3 *db = pParse->db;    /* Database handle */
  Index *pIdx;                 /* An index to being analyzed */
  int iIdxCur;                 /* Cursor open on index being analyzed */
  int iTabCur;                 /* Table cursor */
  Vdbe *v;                     /* The virtual machine being built up */
  int i;                       /* Loop counter */
  int jZeroRows = -1;          /* Jump from here if number of rows is zero */
  int iDb;                     /* Index of database containing pTab */
  u8 needTableCnt = 1;         /* True to count the table */
  int regNewRowid = iMem++;    /* Rowid for the inserted record */
  int regStat4 = iMem++;       /* Register to hold Stat4Accum object */
  int regChng = iMem++;        /* Index of changed index field */
#ifdef SQLITE_ENABLE_STAT4
  int regRowid = iMem++;       /* Rowid argument passed to stat_push() */
#endif
  int regTemp = iMem++;        /* Temporary use register */
  int regTabname = iMem++;     /* Register containing table name */
  int regIdxname = iMem++;     /* Register containing index name */
  int regStat1 = iMem++;       /* Value for the stat column of sqlite_stat1 */
  int regPrev = iMem;          /* MUST BE LAST (see below) */
#ifdef SQLITE_ENABLE_PREUPDATE_HOOK
  Table *pStat1 = 0; 
#endif

  pParse->nMem = MAX(pParse->nMem, iMem);
  v = sqlite3GetVdbe(pParse);
  if( v==0 || NEVER(pTab==0) ){
    return;
  }
  if( pTab->tnum==0 ){
    /* Do not gather statistics on views or virtual tables */
    return;
  }
  if( sqlite3_strlike("sqlite\\_%", pTab->zName, '\\')==0 ){
    /* Do not gather statistics on system tables */
    return;
  }
  assert( sqlite3BtreeHoldsAllMutexes(db) );
  iDb = sqlite3SchemaToIndex(db, pTab->pSchema);
  assert( iDb>=0 );
  assert( sqlite3SchemaMutexHeld(db, iDb, 0) );
#ifndef SQLITE_OMIT_AUTHORIZATION
  if( sqlite3AuthCheck(pParse, SQLITE_ANALYZE, pTab->zName, 0,
      db->aDb[iDb].zDbSName ) ){
    return;
  }
#endif

#ifdef SQLITE_ENABLE_PREUPDATE_HOOK
  if( db->xPreUpdateCallback ){
    pStat1 = (Table*)sqlite3DbMallocZero(db, sizeof(Table) + 13);
    if( pStat1==0 ) return;
    pStat1->zName = (char*)&pStat1[1];
    memcpy(pStat1->zName, "sqlite_stat1", 13);
    pStat1->nCol = 3;
    pStat1->iPKey = -1;
    sqlite3VdbeAddOp4(pParse->pVdbe, OP_Noop, 0, 0, 0,(char*)pStat1,P4_DYNBLOB);
  }
#endif

  /* Establish a read-lock on the table at the shared-cache level. 
  ** Open a read-only cursor on the table. Also allocate a cursor number
  ** to use for scanning indexes (iIdxCur). No index cursor is opened at
  ** this time though.  */
  sqlite3TableLock(pParse, iDb, pTab->tnum, 0, pTab->zName);
  iTabCur = iTab++;
  iIdxCur = iTab++;
  pParse->nTab = MAX(pParse->nTab, iTab);
  sqlite3OpenTable(pParse, iTabCur, iDb, pTab, OP_OpenRead);
  sqlite3VdbeLoadString(v, regTabname, pTab->zName);

  for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
    int nCol;                     /* Number of columns in pIdx. "N" */
    int addrRewind;               /* Address of "OP_Rewind iIdxCur" */
    int addrNextRow;              /* Address of "next_row:" */
    const char *zIdxName;         /* Name of the index */
    int nColTest;                 /* Number of columns to test for changes */

    if( pOnlyIdx && pOnlyIdx!=pIdx ) continue;
    if( pIdx->pPartIdxWhere==0 ) needTableCnt = 0;
    if( !HasRowid(pTab) && IsPrimaryKeyIndex(pIdx) ){
      nCol = pIdx->nKeyCol;
      zIdxName = pTab->zName;
      nColTest = nCol - 1;
    }else{
      nCol = pIdx->nColumn;
      zIdxName = pIdx->zName;
      nColTest = pIdx->uniqNotNull ? pIdx->nKeyCol-1 : nCol-1;
    }

    /* Populate the register containing the index name. */
    sqlite3VdbeLoadString(v, regIdxname, zIdxName);
    VdbeComment((v, "Analysis for %s.%s", pTab->zName, zIdxName));

    /*
    ** Pseudo-code for loop that calls stat_push():
    **
    **   Rewind csr
    **   if eof(csr) goto end_of_scan;
    **   regChng = 0
    **   goto chng_addr_0;
    **
    **  next_row:
    **   regChng = 0
    **   if( idx(0) != regPrev(0) ) goto chng_addr_0
    **   regChng = 1
    **   if( idx(1) != regPrev(1) ) goto chng_addr_1
    **   ...
    **   regChng = N
    **   goto chng_addr_N
    **
    **  chng_addr_0:
    **   regPrev(0) = idx(0)
    **  chng_addr_1:
    **   regPrev(1) = idx(1)
    **  ...
    **
    **  endDistinctTest:
    **   regRowid = idx(rowid)
    **   stat_push(P, regChng, regRowid)
    **   Next csr
    **   if !eof(csr) goto next_row;
    **
    **  end_of_scan:
    */

    /* Make sure there are enough memory cells allocated to accommodate 
    ** the regPrev array and a trailing rowid (the rowid slot is required
    ** when building a record to insert into the sample column of 
    ** the sqlite_stat4 table.  */
    pParse->nMem = MAX(pParse->nMem, regPrev+nColTest);

    /* Open a read-only cursor on the index being analyzed. */
    assert( iDb==sqlite3SchemaToIndex(db, pIdx->pSchema) );
    sqlite3VdbeAddOp3(v, OP_OpenRead, iIdxCur, pIdx->tnum, iDb);
    sqlite3VdbeSetP4KeyInfo(pParse, pIdx);
    VdbeComment((v, "%s", pIdx->zName));

    /* Invoke the stat_init() function. The arguments are:
    ** 
    **    (1) the number of columns in the index including the rowid
    **        (or for a WITHOUT ROWID table, the number of PK columns),
    **    (2) the number of columns in the key without the rowid/pk
    **    (3) the number of rows in the index,
    **
    **
    ** The third argument is only used for STAT4
    */
#ifdef SQLITE_ENABLE_STAT4
    sqlite3VdbeAddOp2(v, OP_Count, iIdxCur, regStat4+3);
#endif
    sqlite3VdbeAddOp2(v, OP_Integer, nCol, regStat4+1);
    sqlite3VdbeAddOp2(v, OP_Integer, pIdx->nKeyCol, regStat4+2);
    sqlite3VdbeAddOp4(v, OP_Function0, 0, regStat4+1, regStat4,
                     (char*)&statInitFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 2+IsStat4);

    /* Implementation of the following:
    **
    **   Rewind csr
    **   if eof(csr) goto end_of_scan;
    **   regChng = 0
    **   goto next_push_0;
    **
    */
    addrRewind = sqlite3VdbeAddOp1(v, OP_Rewind, iIdxCur);
    VdbeCoverage(v);
    sqlite3VdbeAddOp2(v, OP_Integer, 0, regChng);
    addrNextRow = sqlite3VdbeCurrentAddr(v);

    if( nColTest>0 ){
      int endDistinctTest = sqlite3VdbeMakeLabel(pParse);
      int *aGotoChng;               /* Array of jump instruction addresses */
      aGotoChng = sqlite3DbMallocRawNN(db, sizeof(int)*nColTest);
      if( aGotoChng==0 ) continue;

      /*
      **  next_row:
      **   regChng = 0
      **   if( idx(0) != regPrev(0) ) goto chng_addr_0
      **   regChng = 1
      **   if( idx(1) != regPrev(1) ) goto chng_addr_1
      **   ...
      **   regChng = N
      **   goto endDistinctTest
      */
      sqlite3VdbeAddOp0(v, OP_Goto);
      addrNextRow = sqlite3VdbeCurrentAddr(v);
      if( nColTest==1 && pIdx->nKeyCol==1 && IsUniqueIndex(pIdx) ){
        /* For a single-column UNIQUE index, once we have found a non-NULL
        ** row, we know that all the rest will be distinct, so skip 
        ** subsequent distinctness tests. */
        sqlite3VdbeAddOp2(v, OP_NotNull, regPrev, endDistinctTest);
        VdbeCoverage(v);
      }
      for(i=0; i<nColTest; i++){
        char *pColl = (char*)sqlite3LocateCollSeq(pParse, pIdx->azColl[i]);
        sqlite3VdbeAddOp2(v, OP_Integer, i, regChng);
        sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, i, regTemp);
        aGotoChng[i] = 
        sqlite3VdbeAddOp4(v, OP_Ne, regTemp, 0, regPrev+i, pColl, P4_COLLSEQ);
        sqlite3VdbeChangeP5(v, SQLITE_NULLEQ);
        VdbeCoverage(v);
      }
      sqlite3VdbeAddOp2(v, OP_Integer, nColTest, regChng);
      sqlite3VdbeGoto(v, endDistinctTest);
  
  
      /*
      **  chng_addr_0:
      **   regPrev(0) = idx(0)
      **  chng_addr_1:
      **   regPrev(1) = idx(1)
      **  ...
      */
      sqlite3VdbeJumpHere(v, addrNextRow-1);
      for(i=0; i<nColTest; i++){
        sqlite3VdbeJumpHere(v, aGotoChng[i]);
        sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, i, regPrev+i);
      }
      sqlite3VdbeResolveLabel(v, endDistinctTest);
      sqlite3DbFree(db, aGotoChng);
    }
  
    /*
    **  chng_addr_N:
    **   regRowid = idx(rowid)            // STAT4 only
    **   stat_push(P, regChng, regRowid)  // 3rd parameter STAT4 only
    **   Next csr
    **   if !eof(csr) goto next_row;
    */
#ifdef SQLITE_ENABLE_STAT4
    assert( regRowid==(regStat4+2) );
    if( HasRowid(pTab) ){
      sqlite3VdbeAddOp2(v, OP_IdxRowid, iIdxCur, regRowid);
    }else{
      Index *pPk = sqlite3PrimaryKeyIndex(pIdx->pTable);
      int j, k, regKey;
      regKey = sqlite3GetTempRange(pParse, pPk->nKeyCol);
      for(j=0; j<pPk->nKeyCol; j++){
        k = sqlite3ColumnOfIndex(pIdx, pPk->aiColumn[j]);
        assert( k>=0 && k<pIdx->nColumn );
        sqlite3VdbeAddOp3(v, OP_Column, iIdxCur, k, regKey+j);
        VdbeComment((v, "%s", pTab->aCol[pPk->aiColumn[j]].zName));
      }
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regKey, pPk->nKeyCol, regRowid);
      sqlite3ReleaseTempRange(pParse, regKey, pPk->nKeyCol);
    }
#endif
    assert( regChng==(regStat4+1) );
    sqlite3VdbeAddOp4(v, OP_Function0, 1, regStat4, regTemp,
                     (char*)&statPushFuncdef, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, 2+IsStat4);
    sqlite3VdbeAddOp2(v, OP_Next, iIdxCur, addrNextRow); VdbeCoverage(v);

    /* Add the entry to the stat1 table. */
    callStatGet(v, regStat4, STAT_GET_STAT1, regStat1);
    assert( "BBB"[0]==SQLITE_AFF_TEXT );
    sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 3, regTemp, "BBB", 0);
    sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur, regNewRowid);
    sqlite3VdbeAddOp3(v, OP_Insert, iStatCur, regTemp, regNewRowid);
#ifdef SQLITE_ENABLE_PREUPDATE_HOOK
    sqlite3VdbeChangeP4(v, -1, (char*)pStat1, P4_TABLE);
#endif
    sqlite3VdbeChangeP5(v, OPFLAG_APPEND);

    /* Add the entries to the stat4 table. */
#ifdef SQLITE_ENABLE_STAT4
    {
      int regEq = regStat1;
      int regLt = regStat1+1;
      int regDLt = regStat1+2;
      int regSample = regStat1+3;
      int regCol = regStat1+4;
      int regSampleRowid = regCol + nCol;
      int addrNext;
      int addrIsNull;
      u8 seekOp = HasRowid(pTab) ? OP_NotExists : OP_NotFound;

      pParse->nMem = MAX(pParse->nMem, regCol+nCol);

      addrNext = sqlite3VdbeCurrentAddr(v);
      callStatGet(v, regStat4, STAT_GET_ROWID, regSampleRowid);
      addrIsNull = sqlite3VdbeAddOp1(v, OP_IsNull, regSampleRowid);
      VdbeCoverage(v);
      callStatGet(v, regStat4, STAT_GET_NEQ, regEq);
      callStatGet(v, regStat4, STAT_GET_NLT, regLt);
      callStatGet(v, regStat4, STAT_GET_NDLT, regDLt);
      sqlite3VdbeAddOp4Int(v, seekOp, iTabCur, addrNext, regSampleRowid, 0);
      VdbeCoverage(v);
      for(i=0; i<nCol; i++){
        sqlite3ExprCodeLoadIndexColumn(pParse, pIdx, iTabCur, i, regCol+i);
      }
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regCol, nCol, regSample);
      sqlite3VdbeAddOp3(v, OP_MakeRecord, regTabname, 6, regTemp);
      sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur+1, regNewRowid);
      sqlite3VdbeAddOp3(v, OP_Insert, iStatCur+1, regTemp, regNewRowid);
      sqlite3VdbeAddOp2(v, OP_Goto, 1, addrNext); /* P1==1 for end-of-loop */
      sqlite3VdbeJumpHere(v, addrIsNull);
    }
#endif /* SQLITE_ENABLE_STAT4 */

    /* End of analysis */
    sqlite3VdbeJumpHere(v, addrRewind);
  }


  /* Create a single sqlite_stat1 entry containing NULL as the index
  ** name and the row count as the content.
  */
  if( pOnlyIdx==0 && needTableCnt ){
    VdbeComment((v, "%s", pTab->zName));
    sqlite3VdbeAddOp2(v, OP_Count, iTabCur, regStat1);
    jZeroRows = sqlite3VdbeAddOp1(v, OP_IfNot, regStat1); VdbeCoverage(v);
    sqlite3VdbeAddOp2(v, OP_Null, 0, regIdxname);
    assert( "BBB"[0]==SQLITE_AFF_TEXT );
    sqlite3VdbeAddOp4(v, OP_MakeRecord, regTabname, 3, regTemp, "BBB", 0);
    sqlite3VdbeAddOp2(v, OP_NewRowid, iStatCur, regNewRowid);
    sqlite3VdbeAddOp3(v, OP_Insert, iStatCur, regTemp, regNewRowid);
    sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
#ifdef SQLITE_ENABLE_PREUPDATE_HOOK
    sqlite3VdbeChangeP4(v, -1, (char*)pStat1, P4_TABLE);
#endif
    sqlite3VdbeJumpHere(v, jZeroRows);
  }
}