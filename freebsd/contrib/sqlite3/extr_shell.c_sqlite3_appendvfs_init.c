#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ szOsFile; int /*<<< orphan*/  iVersion; } ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_api_routines ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {scalar_t__ szOsFile; TYPE_1__* pAppData; int /*<<< orphan*/  iVersion; } ;
typedef  int /*<<< orphan*/  ApndFile ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_EXTENSION_INIT2 (int /*<<< orphan*/  const*) ; 
 int SQLITE_OK ; 
 int SQLITE_OK_LOAD_PERMANENTLY ; 
 TYPE_2__ apnd_vfs ; 
 scalar_t__ apndvfsRegister ; 
 int sqlite3_auto_extension (void (*) ()) ; 
 TYPE_1__* sqlite3_vfs_find (int /*<<< orphan*/ ) ; 
 int sqlite3_vfs_register (TYPE_2__*,int /*<<< orphan*/ ) ; 

int sqlite3_appendvfs_init(
  sqlite3 *db, 
  char **pzErrMsg, 
  const sqlite3_api_routines *pApi
){
  int rc = SQLITE_OK;
  sqlite3_vfs *pOrig;
  SQLITE_EXTENSION_INIT2(pApi);
  (void)pzErrMsg;
  (void)db;
  pOrig = sqlite3_vfs_find(0);
  apnd_vfs.iVersion = pOrig->iVersion;
  apnd_vfs.pAppData = pOrig;
  apnd_vfs.szOsFile = pOrig->szOsFile + sizeof(ApndFile);
  rc = sqlite3_vfs_register(&apnd_vfs, 0);
#ifdef APPENDVFS_TEST
  if( rc==SQLITE_OK ){
    rc = sqlite3_auto_extension((void(*)(void))apndvfsRegister);
  }
#endif
  if( rc==SQLITE_OK ) rc = SQLITE_OK_LOAD_PERMANENTLY;
  return rc;
}