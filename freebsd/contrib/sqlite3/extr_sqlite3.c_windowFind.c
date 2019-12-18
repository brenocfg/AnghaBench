#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  zName; struct TYPE_4__* pNextWin; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static Window *windowFind(Parse *pParse, Window *pList, const char *zName){
  Window *p;
  for(p=pList; p; p=p->pNextWin){
    if( sqlite3StrICmp(p->zName, zName)==0 ) break;
  }
  if( p==0 ){
    sqlite3ErrorMsg(pParse, "no such window: %s", zName);
  }
  return p;
}