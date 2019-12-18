#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {scalar_t__ eState; scalar_t__ pKey; int nKey; scalar_t__ curIntKey; } ;
typedef  TYPE_1__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_VALID ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int cursorHoldsMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3BtreeIntegerKey (TYPE_1__*) ; 
 int sqlite3BtreePayload (TYPE_1__*,int /*<<< orphan*/ ,int,void*) ; 
 int sqlite3BtreePayloadSize (TYPE_1__*) ; 
 void* sqlite3Malloc (int) ; 
 int /*<<< orphan*/  sqlite3_free (void*) ; 

__attribute__((used)) static int saveCursorKey(BtCursor *pCur){
  int rc = SQLITE_OK;
  assert( CURSOR_VALID==pCur->eState );
  assert( 0==pCur->pKey );
  assert( cursorHoldsMutex(pCur) );

  if( pCur->curIntKey ){
    /* Only the rowid is required for a table btree */
    pCur->nKey = sqlite3BtreeIntegerKey(pCur);
  }else{
    /* For an index btree, save the complete key content. It is possible
    ** that the current key is corrupt. In that case, it is possible that
    ** the sqlite3VdbeRecordUnpack() function may overread the buffer by
    ** up to the size of 1 varint plus 1 8-byte value when the cursor 
    ** position is restored. Hence the 17 bytes of padding allocated 
    ** below. */
    void *pKey;
    pCur->nKey = sqlite3BtreePayloadSize(pCur);
    pKey = sqlite3Malloc( pCur->nKey + 9 + 8 );
    if( pKey ){
      rc = sqlite3BtreePayload(pCur, 0, (int)pCur->nKey, pKey);
      if( rc==SQLITE_OK ){
        memset(((u8*)pKey)+pCur->nKey, 0, 9+8);
        pCur->pKey = pKey;
      }else{
        sqlite3_free(pKey);
      }
    }else{
      rc = SQLITE_NOMEM_BKPT;
    }
  }
  assert( !pCur->curIntKey || !pCur->pKey );
  return rc;
}