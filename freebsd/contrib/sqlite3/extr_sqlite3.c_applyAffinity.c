#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ Mem ;

/* Variables and functions */
 int MEM_Int ; 
 int MEM_IntReal ; 
 int MEM_Real ; 
 int MEM_Str ; 
 char SQLITE_AFF_INTEGER ; 
 char SQLITE_AFF_NUMERIC ; 
 char SQLITE_AFF_REAL ; 
 char SQLITE_AFF_TEXT ; 
 int /*<<< orphan*/  applyNumericAffinity (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeIntegerAffinity (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemStringify (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void applyAffinity(
  Mem *pRec,          /* The value to apply affinity to */
  char affinity,      /* The affinity to be applied */
  u8 enc              /* Use this text encoding */
){
  if( affinity>=SQLITE_AFF_NUMERIC ){
    assert( affinity==SQLITE_AFF_INTEGER || affinity==SQLITE_AFF_REAL
             || affinity==SQLITE_AFF_NUMERIC );
    if( (pRec->flags & MEM_Int)==0 ){ /*OPTIMIZATION-IF-FALSE*/
      if( (pRec->flags & MEM_Real)==0 ){
        if( pRec->flags & MEM_Str ) applyNumericAffinity(pRec,1);
      }else{
        sqlite3VdbeIntegerAffinity(pRec);
      }
    }
  }else if( affinity==SQLITE_AFF_TEXT ){
    /* Only attempt the conversion to TEXT if there is an integer or real
    ** representation (blob and NULL do not get converted) but no string
    ** representation.  It would be harmless to repeat the conversion if 
    ** there is already a string rep, but it is pointless to waste those
    ** CPU cycles. */
    if( 0==(pRec->flags&MEM_Str) ){ /*OPTIMIZATION-IF-FALSE*/
      if( (pRec->flags&(MEM_Real|MEM_Int|MEM_IntReal)) ){
        testcase( pRec->flags & MEM_Int );
        testcase( pRec->flags & MEM_Real );
        testcase( pRec->flags & MEM_IntReal );
        sqlite3VdbeMemStringify(pRec, enc, 1);
      }
    }
    pRec->flags &= ~(MEM_Real|MEM_Int|MEM_IntReal);
  }
}