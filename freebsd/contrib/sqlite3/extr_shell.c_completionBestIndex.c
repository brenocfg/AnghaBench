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
struct sqlite3_index_constraint {scalar_t__ usable; scalar_t__ op; int iColumn; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; int idxNum; double estimatedCost; int estimatedRows; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int argvIndex; int omit; } ;

/* Variables and functions */
#define  COMPLETION_COLUMN_PREFIX 129 
#define  COMPLETION_COLUMN_WHOLELINE 128 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 

__attribute__((used)) static int completionBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i;                 /* Loop over constraints */
  int idxNum = 0;        /* The query plan bitmask */
  int prefixIdx = -1;    /* Index of the start= constraint, or -1 if none */
  int wholelineIdx = -1; /* Index of the stop= constraint, or -1 if none */
  int nArg = 0;          /* Number of arguments that completeFilter() expects */
  const struct sqlite3_index_constraint *pConstraint;

  (void)(tab);    /* Unused parameter */
  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->usable==0 ) continue;
    if( pConstraint->op!=SQLITE_INDEX_CONSTRAINT_EQ ) continue;
    switch( pConstraint->iColumn ){
      case COMPLETION_COLUMN_PREFIX:
        prefixIdx = i;
        idxNum |= 1;
        break;
      case COMPLETION_COLUMN_WHOLELINE:
        wholelineIdx = i;
        idxNum |= 2;
        break;
    }
  }
  if( prefixIdx>=0 ){
    pIdxInfo->aConstraintUsage[prefixIdx].argvIndex = ++nArg;
    pIdxInfo->aConstraintUsage[prefixIdx].omit = 1;
  }
  if( wholelineIdx>=0 ){
    pIdxInfo->aConstraintUsage[wholelineIdx].argvIndex = ++nArg;
    pIdxInfo->aConstraintUsage[wholelineIdx].omit = 1;
  }
  pIdxInfo->idxNum = idxNum;
  pIdxInfo->estimatedCost = (double)5000 - 1000*nArg;
  pIdxInfo->estimatedRows = 500 - 100*nArg;
  return SQLITE_OK;
}