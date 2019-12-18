#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * pVtab; } ;
struct TYPE_13__ {scalar_t__ opcode; int p3; int p2; scalar_t__ p4type; TYPE_1__ p4; } ;
typedef  TYPE_2__ VdbeOp ;
typedef  int /*<<< orphan*/  Vdbe ;
typedef  int /*<<< orphan*/  VTable ;
struct TYPE_14__ {int tnum; TYPE_5__* pIndex; } ;
typedef  TYPE_3__ Table ;
struct TYPE_16__ {int tnum; struct TYPE_16__* pNext; } ;
struct TYPE_15__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_4__ Parse ;
typedef  TYPE_5__ Index ;

/* Variables and functions */
 scalar_t__ IsVirtual (TYPE_3__*) ; 
 scalar_t__ OP_OpenRead ; 
 scalar_t__ OP_VOpen ; 
 scalar_t__ P4_VTAB ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3GetVTable (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_4__*) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 TYPE_2__* sqlite3VdbeGetOp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int readsTable(Parse *p, int iDb, Table *pTab){
  Vdbe *v = sqlite3GetVdbe(p);
  int i;
  int iEnd = sqlite3VdbeCurrentAddr(v);
#ifndef SQLITE_OMIT_VIRTUALTABLE
  VTable *pVTab = IsVirtual(pTab) ? sqlite3GetVTable(p->db, pTab) : 0;
#endif

  for(i=1; i<iEnd; i++){
    VdbeOp *pOp = sqlite3VdbeGetOp(v, i);
    assert( pOp!=0 );
    if( pOp->opcode==OP_OpenRead && pOp->p3==iDb ){
      Index *pIndex;
      int tnum = pOp->p2;
      if( tnum==pTab->tnum ){
        return 1;
      }
      for(pIndex=pTab->pIndex; pIndex; pIndex=pIndex->pNext){
        if( tnum==pIndex->tnum ){
          return 1;
        }
      }
    }
#ifndef SQLITE_OMIT_VIRTUALTABLE
    if( pOp->opcode==OP_VOpen && pOp->p4.pVtab==pVTab ){
      assert( pOp->p4.pVtab!=0 );
      assert( pOp->p4type==P4_VTAB );
      return 1;
    }
#endif
  }
  return 0;
}