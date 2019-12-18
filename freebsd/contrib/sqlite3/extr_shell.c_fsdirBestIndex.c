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
struct sqlite3_index_constraint {scalar_t__ op; int iColumn; int /*<<< orphan*/  usable; } ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int nConstraint; int idxNum; int estimatedRows; double estimatedCost; TYPE_1__* aConstraintUsage; struct sqlite3_index_constraint* aConstraint; } ;
typedef  TYPE_2__ sqlite3_index_info ;
struct TYPE_4__ {int omit; int argvIndex; } ;

/* Variables and functions */
#define  FSDIR_COLUMN_DIR 129 
#define  FSDIR_COLUMN_PATH 128 
 int SQLITE_CONSTRAINT ; 
 scalar_t__ SQLITE_INDEX_CONSTRAINT_EQ ; 
 int SQLITE_OK ; 

__attribute__((used)) static int fsdirBestIndex(
  sqlite3_vtab *tab,
  sqlite3_index_info *pIdxInfo
){
  int i;                 /* Loop over constraints */
  int idxPath = -1;      /* Index in pIdxInfo->aConstraint of PATH= */
  int idxDir = -1;       /* Index in pIdxInfo->aConstraint of DIR= */
  int seenPath = 0;      /* True if an unusable PATH= constraint is seen */
  int seenDir = 0;       /* True if an unusable DIR= constraint is seen */
  const struct sqlite3_index_constraint *pConstraint;

  (void)tab;
  pConstraint = pIdxInfo->aConstraint;
  for(i=0; i<pIdxInfo->nConstraint; i++, pConstraint++){
    if( pConstraint->op!=SQLITE_INDEX_CONSTRAINT_EQ ) continue;
    switch( pConstraint->iColumn ){
      case FSDIR_COLUMN_PATH: {
        if( pConstraint->usable ){
          idxPath = i;
          seenPath = 0;
        }else if( idxPath<0 ){
          seenPath = 1;
        }
        break;
      }
      case FSDIR_COLUMN_DIR: {
        if( pConstraint->usable ){
          idxDir = i;
          seenDir = 0;
        }else if( idxDir<0 ){
          seenDir = 1;
        }
        break;
      }
    } 
  }
  if( seenPath || seenDir ){
    /* If input parameters are unusable, disallow this plan */
    return SQLITE_CONSTRAINT;
  }

  if( idxPath<0 ){
    pIdxInfo->idxNum = 0;
    /* The pIdxInfo->estimatedCost should have been initialized to a huge
    ** number.  Leave it unchanged. */
    pIdxInfo->estimatedRows = 0x7fffffff;
  }else{
    pIdxInfo->aConstraintUsage[idxPath].omit = 1;
    pIdxInfo->aConstraintUsage[idxPath].argvIndex = 1;
    if( idxDir>=0 ){
      pIdxInfo->aConstraintUsage[idxDir].omit = 1;
      pIdxInfo->aConstraintUsage[idxDir].argvIndex = 2;
      pIdxInfo->idxNum = 2;
      pIdxInfo->estimatedCost = 10.0;
    }else{
      pIdxInfo->idxNum = 1;
      pIdxInfo->estimatedCost = 100.0;
    }
  }

  return SQLITE_OK;
}