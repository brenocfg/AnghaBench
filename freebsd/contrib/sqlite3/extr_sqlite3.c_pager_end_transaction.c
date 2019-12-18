#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ eState; scalar_t__ eLock; scalar_t__ pInJournal; scalar_t__ journalMode; scalar_t__ journalOff; scalar_t__ dbSize; scalar_t__ dbFileSize; scalar_t__ setMaster; scalar_t__ changeCountDone; int /*<<< orphan*/  pWal; scalar_t__ exclusiveMode; int /*<<< orphan*/  fd; int /*<<< orphan*/  pPCache; scalar_t__ nRec; int /*<<< orphan*/  extraSync; int /*<<< orphan*/  zJournal; int /*<<< orphan*/  pVfs; int /*<<< orphan*/  jfd; scalar_t__ tempFile; int /*<<< orphan*/  syncFlags; scalar_t__ fullSync; } ;
struct TYPE_14__ {scalar_t__ pageHash; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 scalar_t__ EXCLUSIVE_LOCK ; 
 scalar_t__ MEMDB ; 
 scalar_t__ PAGER_ERROR ; 
 scalar_t__ PAGER_JOURNALMODE_DELETE ; 
 scalar_t__ PAGER_JOURNALMODE_MEMORY ; 
 scalar_t__ PAGER_JOURNALMODE_PERSIST ; 
 scalar_t__ PAGER_JOURNALMODE_TRUNCATE ; 
 scalar_t__ PAGER_JOURNALMODE_WAL ; 
 scalar_t__ PAGER_READER ; 
 scalar_t__ PAGER_WRITER_LOCKED ; 
 scalar_t__ RESERVED_LOCK ; 
 int /*<<< orphan*/  SHARED_LOCK ; 
 int /*<<< orphan*/  SQLITE_FCNTL_COMMIT_PHASETWO ; 
 int SQLITE_IOCAP_BATCH_ATOMIC ; 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_2__*) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 
 scalar_t__ pagerFlushOnCommit (TYPE_2__*,int) ; 
 int pagerUnlockDb (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pagerUseWal (TYPE_2__*) ; 
 int /*<<< orphan*/  pager_set_pagehash ; 
 int pager_truncate (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  releaseAllSavepoints (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BitvecDestroy (scalar_t__) ; 
 scalar_t__ sqlite3JournalIsInMemory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ ) ; 
 int sqlite3OsDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3OsDeviceCharacteristics (int /*<<< orphan*/ ) ; 
 int sqlite3OsFileControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3OsSync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3OsTruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* sqlite3PagerLookup (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3PagerUnrefNotNull (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3PcacheCleanAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PcacheClearWritable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PcacheIterateDirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3PcacheRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PcacheTruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int sqlite3WalEndWriteTransaction (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3WalExclusiveMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zeroJournalHdr (TYPE_2__*,int) ; 

__attribute__((used)) static int pager_end_transaction(Pager *pPager, int hasMaster, int bCommit){
  int rc = SQLITE_OK;      /* Error code from journal finalization operation */
  int rc2 = SQLITE_OK;     /* Error code from db file unlock operation */

  /* Do nothing if the pager does not have an open write transaction
  ** or at least a RESERVED lock. This function may be called when there
  ** is no write-transaction active but a RESERVED or greater lock is
  ** held under two circumstances:
  **
  **   1. After a successful hot-journal rollback, it is called with
  **      eState==PAGER_NONE and eLock==EXCLUSIVE_LOCK.
  **
  **   2. If a connection with locking_mode=exclusive holding an EXCLUSIVE 
  **      lock switches back to locking_mode=normal and then executes a
  **      read-transaction, this function is called with eState==PAGER_READER 
  **      and eLock==EXCLUSIVE_LOCK when the read-transaction is closed.
  */
  assert( assert_pager_state(pPager) );
  assert( pPager->eState!=PAGER_ERROR );
  if( pPager->eState<PAGER_WRITER_LOCKED && pPager->eLock<RESERVED_LOCK ){
    return SQLITE_OK;
  }

  releaseAllSavepoints(pPager);
  assert( isOpen(pPager->jfd) || pPager->pInJournal==0 
      || (sqlite3OsDeviceCharacteristics(pPager->fd)&SQLITE_IOCAP_BATCH_ATOMIC)
  );
  if( isOpen(pPager->jfd) ){
    assert( !pagerUseWal(pPager) );

    /* Finalize the journal file. */
    if( sqlite3JournalIsInMemory(pPager->jfd) ){
      /* assert( pPager->journalMode==PAGER_JOURNALMODE_MEMORY ); */
      sqlite3OsClose(pPager->jfd);
    }else if( pPager->journalMode==PAGER_JOURNALMODE_TRUNCATE ){
      if( pPager->journalOff==0 ){
        rc = SQLITE_OK;
      }else{
        rc = sqlite3OsTruncate(pPager->jfd, 0);
        if( rc==SQLITE_OK && pPager->fullSync ){
          /* Make sure the new file size is written into the inode right away.
          ** Otherwise the journal might resurrect following a power loss and
          ** cause the last transaction to roll back.  See
          ** https://bugzilla.mozilla.org/show_bug.cgi?id=1072773
          */
          rc = sqlite3OsSync(pPager->jfd, pPager->syncFlags);
        }
      }
      pPager->journalOff = 0;
    }else if( pPager->journalMode==PAGER_JOURNALMODE_PERSIST
      || (pPager->exclusiveMode && pPager->journalMode!=PAGER_JOURNALMODE_WAL)
    ){
      rc = zeroJournalHdr(pPager, hasMaster||pPager->tempFile);
      pPager->journalOff = 0;
    }else{
      /* This branch may be executed with Pager.journalMode==MEMORY if
      ** a hot-journal was just rolled back. In this case the journal
      ** file should be closed and deleted. If this connection writes to
      ** the database file, it will do so using an in-memory journal.
      */
      int bDelete = !pPager->tempFile;
      assert( sqlite3JournalIsInMemory(pPager->jfd)==0 );
      assert( pPager->journalMode==PAGER_JOURNALMODE_DELETE 
           || pPager->journalMode==PAGER_JOURNALMODE_MEMORY 
           || pPager->journalMode==PAGER_JOURNALMODE_WAL 
      );
      sqlite3OsClose(pPager->jfd);
      if( bDelete ){
        rc = sqlite3OsDelete(pPager->pVfs, pPager->zJournal, pPager->extraSync);
      }
    }
  }

#ifdef SQLITE_CHECK_PAGES
  sqlite3PcacheIterateDirty(pPager->pPCache, pager_set_pagehash);
  if( pPager->dbSize==0 && sqlite3PcacheRefCount(pPager->pPCache)>0 ){
    PgHdr *p = sqlite3PagerLookup(pPager, 1);
    if( p ){
      p->pageHash = 0;
      sqlite3PagerUnrefNotNull(p);
    }
  }
#endif

  sqlite3BitvecDestroy(pPager->pInJournal);
  pPager->pInJournal = 0;
  pPager->nRec = 0;
  if( rc==SQLITE_OK ){
    if( MEMDB || pagerFlushOnCommit(pPager, bCommit) ){
      sqlite3PcacheCleanAll(pPager->pPCache);
    }else{
      sqlite3PcacheClearWritable(pPager->pPCache);
    }
    sqlite3PcacheTruncate(pPager->pPCache, pPager->dbSize);
  }

  if( pagerUseWal(pPager) ){
    /* Drop the WAL write-lock, if any. Also, if the connection was in 
    ** locking_mode=exclusive mode but is no longer, drop the EXCLUSIVE 
    ** lock held on the database file.
    */
    rc2 = sqlite3WalEndWriteTransaction(pPager->pWal);
    assert( rc2==SQLITE_OK );
  }else if( rc==SQLITE_OK && bCommit && pPager->dbFileSize>pPager->dbSize ){
    /* This branch is taken when committing a transaction in rollback-journal
    ** mode if the database file on disk is larger than the database image.
    ** At this point the journal has been finalized and the transaction 
    ** successfully committed, but the EXCLUSIVE lock is still held on the
    ** file. So it is safe to truncate the database file to its minimum
    ** required size.  */
    assert( pPager->eLock==EXCLUSIVE_LOCK );
    rc = pager_truncate(pPager, pPager->dbSize);
  }

  if( rc==SQLITE_OK && bCommit ){
    rc = sqlite3OsFileControl(pPager->fd, SQLITE_FCNTL_COMMIT_PHASETWO, 0);
    if( rc==SQLITE_NOTFOUND ) rc = SQLITE_OK;
  }

  if( !pPager->exclusiveMode 
   && (!pagerUseWal(pPager) || sqlite3WalExclusiveMode(pPager->pWal, 0))
  ){
    rc2 = pagerUnlockDb(pPager, SHARED_LOCK);
    pPager->changeCountDone = 0;
  }
  pPager->eState = PAGER_READER;
  pPager->setMaster = 0;

  return (rc==SQLITE_OK?rc2:rc);
}