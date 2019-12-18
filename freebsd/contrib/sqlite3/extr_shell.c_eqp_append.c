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
struct TYPE_8__ {int iEqpId; int iParentId; struct TYPE_8__* pNext; int /*<<< orphan*/  zText; } ;
struct TYPE_6__ {TYPE_3__* pLast; TYPE_3__* pRow; } ;
struct TYPE_7__ {TYPE_1__ sGraph; int /*<<< orphan*/  out; scalar_t__ autoEQPtest; } ;
typedef  TYPE_2__ ShellState ;
typedef  TYPE_3__ EQPGraphRow ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  shell_out_of_memory () ; 
 TYPE_3__* sqlite3_malloc64 (int) ; 
 int strlen30 (char const*) ; 
 int /*<<< orphan*/  utf8_printf (int /*<<< orphan*/ ,char*,int,int,char const*) ; 

__attribute__((used)) static void eqp_append(ShellState *p, int iEqpId, int p2, const char *zText){
  EQPGraphRow *pNew;
  int nText = strlen30(zText);
  if( p->autoEQPtest ){
    utf8_printf(p->out, "%d,%d,%s\n", iEqpId, p2, zText);
  }
  pNew = sqlite3_malloc64( sizeof(*pNew) + nText );
  if( pNew==0 ) shell_out_of_memory();
  pNew->iEqpId = iEqpId;
  pNew->iParentId = p2;
  memcpy(pNew->zText, zText, nText+1);
  pNew->pNext = 0;
  if( p->sGraph.pLast ){
    p->sGraph.pLast->pNext = pNew;
  }else{
    p->sGraph.pRow = pNew;
  }
  p->sGraph.pLast = pNew;
}