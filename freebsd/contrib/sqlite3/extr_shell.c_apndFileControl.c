#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_10__ {int /*<<< orphan*/  iPgOne; } ;
struct TYPE_8__ {int (* xFileControl ) (TYPE_2__*,int,void*) ;} ;
typedef  TYPE_3__ ApndFile ;

/* Variables and functions */
 TYPE_2__* ORIGFILE (TYPE_2__*) ; 
 int SQLITE_FCNTL_VFSNAME ; 
 int SQLITE_OK ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_2__*,int,void*) ; 

__attribute__((used)) static int apndFileControl(sqlite3_file *pFile, int op, void *pArg){
  ApndFile *p = (ApndFile *)pFile;
  int rc;
  pFile = ORIGFILE(pFile);
  rc = pFile->pMethods->xFileControl(pFile, op, pArg);
  if( rc==SQLITE_OK && op==SQLITE_FCNTL_VFSNAME ){
    *(char**)pArg = sqlite3_mprintf("apnd(%lld)/%z", p->iPgOne, *(char**)pArg);
  }
  return rc;
}