#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nLock; scalar_t__ bProcessLock; int /*<<< orphan*/  pLockMutex; } ;
typedef  TYPE_1__ unixInodeInfo ;
struct TYPE_8__ {TYPE_1__* pInode; } ;
typedef  TYPE_2__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int /*<<< orphan*/  NO_LOCK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int closeUnixFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releaseInodeInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  setPendingFd (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unixEnterMutex () ; 
 int unixFileMutexNotheld (TYPE_2__*) ; 
 int /*<<< orphan*/  unixLeaveMutex () ; 
 int /*<<< orphan*/  unixUnlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verifyDbFile (TYPE_2__*) ; 

__attribute__((used)) static int unixClose(sqlite3_file *id){
  int rc = SQLITE_OK;
  unixFile *pFile = (unixFile *)id;
  unixInodeInfo *pInode = pFile->pInode;

  assert( pInode!=0 );
  verifyDbFile(pFile);
  unixUnlock(id, NO_LOCK);
  assert( unixFileMutexNotheld(pFile) );
  unixEnterMutex();

  /* unixFile.pInode is always valid here. Otherwise, a different close
  ** routine (e.g. nolockClose()) would be called instead.
  */
  assert( pFile->pInode->nLock>0 || pFile->pInode->bProcessLock==0 );
  sqlite3_mutex_enter(pInode->pLockMutex);
  if( pInode->nLock ){
    /* If there are outstanding locks, do not actually close the file just
    ** yet because that would clear those locks.  Instead, add the file
    ** descriptor to pInode->pUnused list.  It will be automatically closed 
    ** when the last lock is cleared.
    */
    setPendingFd(pFile);
  }
  sqlite3_mutex_leave(pInode->pLockMutex);
  releaseInodeInfo(pFile);
  rc = closeUnixFile(id);
  unixLeaveMutex();
  return rc;
}