#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
struct TYPE_11__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_12__ {scalar_t__ iPgOne; scalar_t__ iMark; } ;
struct TYPE_10__ {int (* xTruncate ) (TYPE_2__*,scalar_t__) ;} ;
typedef  TYPE_3__ ApndFile ;

/* Variables and functions */
 scalar_t__ APND_MARK_SIZE ; 
 TYPE_2__* ORIGFILE (TYPE_2__*) ; 
 int SQLITE_OK ; 
 int apndWriteMark (TYPE_3__*,TYPE_2__*) ; 
 int stub1 (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int apndTruncate(sqlite3_file *pFile, sqlite_int64 size){
  int rc;
  ApndFile *p = (ApndFile *)pFile;
  pFile = ORIGFILE(pFile);
  rc = pFile->pMethods->xTruncate(pFile, size+p->iPgOne+APND_MARK_SIZE);
  if( rc==SQLITE_OK ){
    p->iMark = p->iPgOne+size;
    rc = apndWriteMark(p, pFile);
  }
  return rc;
}