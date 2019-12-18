#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {scalar_t__ aLTerm; scalar_t__ aLTermSpace; } ;
typedef  TYPE_1__ WhereLoop ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  whereLoopClearUnion (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  whereLoopInit (TYPE_1__*) ; 

__attribute__((used)) static void whereLoopClear(sqlite3 *db, WhereLoop *p){
  if( p->aLTerm!=p->aLTermSpace ) sqlite3DbFreeNN(db, p->aLTerm);
  whereLoopClearUnion(db, p);
  whereLoopInit(p);
}