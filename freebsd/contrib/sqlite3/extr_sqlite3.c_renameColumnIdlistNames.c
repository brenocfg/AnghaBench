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
struct TYPE_5__ {int nId; TYPE_1__* a; } ;
struct TYPE_4__ {char* zName; } ;
typedef  int /*<<< orphan*/  RenameCtx ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_2__ IdList ;

/* Variables and functions */
 int /*<<< orphan*/  renameTokenFind (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ sqlite3_stricmp (char*,char const*) ; 

__attribute__((used)) static void renameColumnIdlistNames(
  Parse *pParse, 
  RenameCtx *pCtx, 
  IdList *pIdList, 
  const char *zOld
){
  if( pIdList ){
    int i;
    for(i=0; i<pIdList->nId; i++){
      char *zName = pIdList->a[i].zName;
      if( 0==sqlite3_stricmp(zName, zOld) ){
        renameTokenFind(pParse, pCtx, (void*)zName);
      }
    }
  }
}