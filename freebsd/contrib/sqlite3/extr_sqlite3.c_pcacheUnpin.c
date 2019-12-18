#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pCache; scalar_t__ bPurgeable; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* xUnpin ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__ pcache2; } ;
struct TYPE_7__ {TYPE_5__* pCache; int /*<<< orphan*/  pPage; int /*<<< orphan*/  pgno; } ;
typedef  TYPE_2__ PgHdr ;

/* Variables and functions */
 int /*<<< orphan*/  pcacheDump (TYPE_5__*) ; 
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 TYPE_3__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcacheUnpin(PgHdr *p){
  if( p->pCache->bPurgeable ){
    pcacheTrace(("%p.UNPIN %d\n", p->pCache, p->pgno));
    sqlite3GlobalConfig.pcache2.xUnpin(p->pCache->pCache, p->pPage, 0);
    pcacheDump(p->pCache);
  }
}