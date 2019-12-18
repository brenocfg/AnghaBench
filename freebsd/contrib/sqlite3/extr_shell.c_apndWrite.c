#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite_int64 ;
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_12__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_13__ {scalar_t__ iPgOne; scalar_t__ iMark; } ;
struct TYPE_11__ {int (* xWrite ) (TYPE_2__*,void const*,int,scalar_t__) ;int (* xFileSize ) (TYPE_2__*,scalar_t__*) ;} ;
typedef  TYPE_3__ ApndFile ;

/* Variables and functions */
 scalar_t__ APND_MARK_SIZE ; 
 scalar_t__ APND_MAX_SIZE ; 
 TYPE_2__* ORIGFILE (TYPE_2__*) ; 
 int SQLITE_FULL ; 
 int SQLITE_OK ; 
 int apndWriteMark (TYPE_3__*,TYPE_2__*) ; 
 int stub1 (TYPE_2__*,void const*,int,scalar_t__) ; 
 int stub2 (TYPE_2__*,scalar_t__*) ; 

__attribute__((used)) static int apndWrite(
  sqlite3_file *pFile,
  const void *zBuf,
  int iAmt,
  sqlite_int64 iOfst
){
  int rc;
  ApndFile *p = (ApndFile *)pFile;
  pFile = ORIGFILE(pFile);
  if( iOfst+iAmt>=APND_MAX_SIZE ) return SQLITE_FULL;
  rc = pFile->pMethods->xWrite(pFile, zBuf, iAmt, iOfst+p->iPgOne);
  if( rc==SQLITE_OK &&  iOfst + iAmt + p->iPgOne > p->iMark ){
    sqlite3_int64 sz = 0;
    rc = pFile->pMethods->xFileSize(pFile, &sz);
    if( rc==SQLITE_OK ){
      p->iMark = sz - APND_MARK_SIZE;
      if( iOfst + iAmt + p->iPgOne > p->iMark ){
        p->iMark = p->iPgOne + iOfst + iAmt;
        rc = apndWriteMark(p, pFile);
      }
    }
  }
  return rc;
}