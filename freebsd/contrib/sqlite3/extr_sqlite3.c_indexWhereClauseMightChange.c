#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pPartIdxWhere; } ;
typedef  TYPE_1__ Index ;

/* Variables and functions */
 int sqlite3ExprReferencesUpdatedColumn (scalar_t__,int*,int) ; 

__attribute__((used)) static int indexWhereClauseMightChange(
  Index *pIdx,      /* The index to check */
  int *aXRef,       /* aXRef[j]>=0 if column j is being updated */
  int chngRowid     /* true if the rowid is being updated */
){
  if( pIdx->pPartIdxWhere==0 ) return 0;
  return sqlite3ExprReferencesUpdatedColumn(pIdx->pPartIdxWhere,
                                            aXRef, chngRowid);
}