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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int funcFlags; } ;
typedef  TYPE_1__ FuncDef ;

/* Variables and functions */
 int SQLITE_FUNC_EPHEM ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void freeEphemeralFunction(sqlite3 *db, FuncDef *pDef){
  if( (pDef->funcFlags & SQLITE_FUNC_EPHEM)!=0 ){
    sqlite3DbFreeNN(db, pDef);
  }
}