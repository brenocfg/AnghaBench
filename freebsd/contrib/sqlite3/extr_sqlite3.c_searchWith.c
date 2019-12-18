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
struct SrcList_item {scalar_t__ zDatabase; char* zName; } ;
struct Cte {int /*<<< orphan*/  zName; } ;
struct TYPE_4__ {int nCte; struct Cte* a; struct TYPE_4__* pOuter; } ;
typedef  TYPE_1__ With ;

/* Variables and functions */
 scalar_t__ sqlite3StrICmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct Cte *searchWith(
  With *pWith,                    /* Current innermost WITH clause */
  struct SrcList_item *pItem,     /* FROM clause element to resolve */
  With **ppContext                /* OUT: WITH clause return value belongs to */
){
  const char *zName;
  if( pItem->zDatabase==0 && (zName = pItem->zName)!=0 ){
    With *p;
    for(p=pWith; p; p=p->pOuter){
      int i;
      for(i=0; i<p->nCte; i++){
        if( sqlite3StrICmp(zName, p->a[i].zName)==0 ){
          *ppContext = p;
          return &p->a[i];
        }
      }
    }
  }
  return 0;
}