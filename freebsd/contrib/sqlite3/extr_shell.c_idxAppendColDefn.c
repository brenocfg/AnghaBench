#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zColl; int /*<<< orphan*/  zName; } ;
struct TYPE_7__ {size_t iCol; scalar_t__ bDesc; int /*<<< orphan*/  zColl; } ;
struct TYPE_6__ {TYPE_3__* aCol; } ;
typedef  TYPE_1__ IdxTable ;
typedef  TYPE_2__ IdxConstraint ;
typedef  TYPE_3__ IdxColumn ;

/* Variables and functions */
 char* idxAppendText (int*,char*,char*,...) ; 
 scalar_t__ idxIdentifierRequiresQuotes (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *idxAppendColDefn(
  int *pRc,                       /* IN/OUT: Error code */
  char *zIn,                      /* Column defn accumulated so far */
  IdxTable *pTab,                 /* Table index will be created on */
  IdxConstraint *pCons
){
  char *zRet = zIn;
  IdxColumn *p = &pTab->aCol[pCons->iCol];
  if( zRet ) zRet = idxAppendText(pRc, zRet, ", ");

  if( idxIdentifierRequiresQuotes(p->zName) ){
    zRet = idxAppendText(pRc, zRet, "%Q", p->zName);
  }else{
    zRet = idxAppendText(pRc, zRet, "%s", p->zName);
  }

  if( sqlite3_stricmp(p->zColl, pCons->zColl) ){
    if( idxIdentifierRequiresQuotes(pCons->zColl) ){
      zRet = idxAppendText(pRc, zRet, " COLLATE %Q", pCons->zColl);
    }else{
      zRet = idxAppendText(pRc, zRet, " COLLATE %s", pCons->zColl);
    }
  }

  if( pCons->bDesc ){
    zRet = idxAppendText(pRc, zRet, " DESC");
  }
  return zRet;
}