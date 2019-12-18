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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int sqlite3_int64 ;
struct TYPE_4__ {int const nVTrans; int /*<<< orphan*/ ** aVTrans; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  int /*<<< orphan*/  VTable ;

/* Variables and functions */
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** sqlite3DbRealloc (TYPE_1__*,void*,int) ; 

__attribute__((used)) static int growVTrans(sqlite3 *db){
  const int ARRAY_INCR = 5;

  /* Grow the sqlite3.aVTrans array if required */
  if( (db->nVTrans%ARRAY_INCR)==0 ){
    VTable **aVTrans;
    sqlite3_int64 nBytes = sizeof(sqlite3_vtab*)*
                                 ((sqlite3_int64)db->nVTrans + ARRAY_INCR);
    aVTrans = sqlite3DbRealloc(db, (void *)db->aVTrans, nBytes);
    if( !aVTrans ){
      return SQLITE_NOMEM_BKPT;
    }
    memset(&aVTrans[db->nVTrans], 0, sizeof(sqlite3_vtab *)*ARRAY_INCR);
    db->aVTrans = aVTrans;
  }

  return SQLITE_OK;
}