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
struct TYPE_4__ {scalar_t__ iCol; struct TYPE_4__* pLink; } ;
typedef  TYPE_1__ IdxConstraint ;

/* Variables and functions */

__attribute__((used)) static int idxFindConstraint(IdxConstraint *pList, IdxConstraint *p){
  IdxConstraint *pCmp;
  for(pCmp=pList; pCmp; pCmp=pCmp->pLink){
    if( p->iCol==pCmp->iCol ) return 1;
  }
  return 0;
}