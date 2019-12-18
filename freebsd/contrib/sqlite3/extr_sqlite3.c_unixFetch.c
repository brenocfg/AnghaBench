#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ mmapSizeMax; scalar_t__ pMapRegion; int mmapSize; int /*<<< orphan*/  nFetchOut; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int i64 ;

/* Variables and functions */
 int SQLITE_OK ; 
 int unixMapfile (TYPE_1__*,int) ; 

__attribute__((used)) static int unixFetch(sqlite3_file *fd, i64 iOff, int nAmt, void **pp){
#if SQLITE_MAX_MMAP_SIZE>0
  unixFile *pFd = (unixFile *)fd;   /* The underlying database file */
#endif
  *pp = 0;

#if SQLITE_MAX_MMAP_SIZE>0
  if( pFd->mmapSizeMax>0 ){
    if( pFd->pMapRegion==0 ){
      int rc = unixMapfile(pFd, -1);
      if( rc!=SQLITE_OK ) return rc;
    }
    if( pFd->mmapSize >= iOff+nAmt ){
      *pp = &((u8 *)pFd->pMapRegion)[iOff];
      pFd->nFetchOut++;
    }
  }
#endif
  return SQLITE_OK;
}